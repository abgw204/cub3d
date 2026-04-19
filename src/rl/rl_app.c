/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_app.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opencode                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19                                #+#    #+#             */
/*   Updated: 2026/04/19                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_rl.h"

#include <stdlib.h>
#include <string.h>

#ifndef CUB3D_RL_RENDER_SCALE
# define CUB3D_RL_RENDER_SCALE 0.5f
#endif

static void	set_null_game(t_game *game)
{
	memset(game, 0, sizeof(*game));
	game->fps = NULL;
	game->keys = NULL;
	game->local_keys = NULL;
	game->map = NULL;
	game->z_buffer = NULL;
}

static void	init_config_rl(t_config *config)
{
	config->show_fps = 0;
	config->show_mouse = true;
}

static int	parse_map_fd(const char *map_path)
{
	int	fd;

	fd = open(map_path, O_RDONLY);
	if (fd < 0)
		return (print_perror());
	if (parse_given_fd(fd))
	{
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static void	reset_players(t_game *game)
{
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		game->players[i].connected = 0;
		game->players[i].id = -1;
		game->players[i].health = 0;
	}
}

static bool	draw_gun_hud(t_rl_ctx *ctx, bool shooting)
{
	const int	frames = 5;
	const float	fps = 53.0f;
	Texture2D	sheet;
	int		frame_w;
	int		frame_h;
	Rectangle	src;
	Rectangle	dst;
	float		scale;
	bool		finished;

	sheet = ctx->assets.gun_sheet;
	finished = false;
	if (sheet.id == 0)
		return (false);
	frame_w = sheet.width / frames;
	frame_h = sheet.height;
	if (frame_w <= 0 || frame_h <= 0)
		return (false);
	if (shooting)
	{
		ctx->gun_anim.acc += (float)g_delta_time;
		while (ctx->gun_anim.acc >= (1.0f / fps))
		{
			ctx->gun_anim.acc -= (1.0f / fps);
			ctx->gun_anim.frame++;
			if (ctx->gun_anim.frame >= frames)
			{
				ctx->gun_anim.frame = 0;
				ctx->gun_anim.acc = 0.0f;
				finished = true;
				break ;
			}
		}
	}
	src.x = (float)(ctx->gun_anim.frame * frame_w);
	src.y = 0.0f;
	src.width = (float)frame_w;
	src.height = (float)frame_h;
	scale = (float)GetScreenWidth() / 1920.0f;
	if (scale < 0.75f)
		scale = 0.75f;
	if (scale > 1.25f)
		scale = 1.25f;
	scale = 5.0f * scale;
	dst.width = (float)frame_w * scale;
	dst.height = (float)frame_h * scale;
	dst.x = (float)GetScreenWidth() / 2.0f;
	dst.y = (float)GetScreenHeight() / 2.0f - 50.0f * (scale / 5.0f);
	DrawTexturePro(sheet, src, dst, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);
	return (finished);
}

int	rl_app_init(t_rl_ctx *ctx, const char *map_path, int my_id,
		const char *server_ip, int port)
{
	t_game	*game;

	memset(ctx, 0, sizeof(*ctx));
	ctx->server_port = port;
	strncpy(ctx->server_ip, server_ip, sizeof(ctx->server_ip) - 1);
	ctx->server_ip[sizeof(ctx->server_ip) - 1] = '\0';

	if (parse_map_fd(map_path))
		return (1);
	ctx->game = (t_game *)calloc(1, sizeof(t_game));
	if (ctx->game == NULL)
		return (print_error("Memory allocation error"));
	game = ctx->game;
	set_null_game(game);
	game->data = get_data();
	game->map = game->data->map;
	game->map_w = game->data->map_w;
	game->map_h = game->data->map_h;
	get_player_info(game);
	init_config_rl(&game->config);
	game->keys = ft_calloc(1, 17);
	game->local_keys = ft_calloc(1, 3);
	if (!game->keys || !game->local_keys)
		return (print_error("Memory allocation error"));
	ft_memset(game->keys, '0', 17);
	ft_memset(game->local_keys, '0', 3);
	game->my_id = my_id;
	memcpy(game->keys + 4, &game->my_id, sizeof(int));
	game->player.speed = 2.0f;
	game->health = 3;
	reset_players(game);
	if (rl_net_init(game, my_id, server_ip, port))
		return (1);

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1920, 1080, "cub3d (raylib)");
	{
		int	monitor;
		int	mw;
		int	mh;

		monitor = GetCurrentMonitor();
		mw = GetMonitorWidth(monitor);
		mh = GetMonitorHeight(monitor);
		ToggleFullscreen();
		SetWindowSize(mw, mh);
	}
	SetTargetFPS(0);
	DisableCursor();

	ctx->scene.target = rl_create_scene_target(GetScreenWidth(), GetScreenHeight());
	ctx->scene.w = ctx->scene.target.texture.width;
	ctx->scene.h = ctx->scene.target.texture.height;
	SetTextureFilter(ctx->scene.target.texture, TEXTURE_FILTER_POINT);
	game->screen_w = ctx->scene.w;
	game->screen_h = ctx->scene.h;
	game->z_buffer = (double *)malloc((size_t)game->screen_w * sizeof(double));
	if (game->z_buffer == NULL)
		return (print_error("Memory allocation error (z_buffer)"));

	if (rl_assets_load(&ctx->assets, game->data))
		return (1);
	ctx->gun_anim.frame = 0;
	ctx->gun_anim.acc = 0.0f;
	ctx->prev_dead = false;
	ctx->want_respawn = false;
	return (0);
}

void	rl_app_tick(t_rl_ctx *ctx)
{
	t_game	*game;
	bool	dead;
	int	want_w;
	int	want_h;

	game = ctx->game;
	set_delta_time(game);
	game->shoot_timer += g_delta_time;
	game->keys[16] = '0';

	dead = (game->health <= 0);
	rl_input_update(ctx);
	if (!dead && game->keys[16] == '1')
	{
		ctx->gun_anim.frame = 0;
		ctx->gun_anim.acc = 0.0f;
		if (ctx->assets.audio_ok)
			PlaySound(ctx->assets.gunshot);
	}
	memcpy(game->keys + 8, &game->player.angle, sizeof(double));
	if (dead && ctx->want_respawn)
	{
		game->keys[16] = '2';
		ctx->want_respawn = false;
	}
	rl_net_send_inputs(game);
	rl_net_receive_state(game);
	free(game->fps);
	game->fps = NULL;

	if (IsWindowResized())
	{
		want_w = (int)((float)GetScreenWidth() * CUB3D_RL_RENDER_SCALE);
		want_h = (int)((float)GetScreenHeight() * CUB3D_RL_RENDER_SCALE);
		want_w = rl_clampi(want_w, 320, GetScreenWidth());
		want_h = rl_clampi(want_h, 180, GetScreenHeight());
		if (want_w != ctx->scene.target.texture.width
			|| want_h != ctx->scene.target.texture.height)
		{
			UnloadRenderTexture(ctx->scene.target);
			ctx->scene.target = LoadRenderTexture(want_w, want_h);
			SetTextureFilter(ctx->scene.target.texture, TEXTURE_FILTER_POINT);
			ctx->scene.w = ctx->scene.target.texture.width;
			ctx->scene.h = ctx->scene.target.texture.height;
			game->screen_w = ctx->scene.w;
			game->screen_h = ctx->scene.h;
			free(game->z_buffer);
			game->z_buffer = (double *)malloc((size_t)game->screen_w * sizeof(double));
			if (game->z_buffer == NULL)
			{
				CloseWindow();
				print_error("Memory allocation error (z_buffer resize)");
				return ;
			}
		}
	}

	rl_render_scene(ctx);
	rl_render_sprites(ctx);

	BeginDrawing();
	ClearBackground((Color){ 18, 18, 20, 255 });
	{
		Rectangle	src;
		Rectangle	dst;

		src = (Rectangle){ 0.0f, 0.0f, (float)ctx->scene.w, -(float)ctx->scene.h };
		dst = (Rectangle){ 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() };
		DrawTexturePro(ctx->scene.target.texture, src, dst,
			(Vector2){0.0f, 0.0f}, 0.0f, WHITE);
	}
	if (!dead)
	{
		if (draw_gun_hud(ctx, game->is_shooting))
			game->is_shooting = false;
	}
	else
	{
		if (rl_ui_draw_death_overlay(GetScreenWidth(), GetScreenHeight()))
			ctx->want_respawn = true;
	}
	DrawFPS(20, 20);
	EndDrawing();
}

void	rl_app_shutdown(t_rl_ctx *ctx)
{
	t_game	*game;

	if (ctx == NULL)
		return ;
	game = ctx->game;
	if (ctx->scene.target.id != 0)
		UnloadRenderTexture(ctx->scene.target);
	rl_assets_unload(&ctx->assets);
	if (game != NULL)
	{
		free(game->z_buffer);
		if (game->soc.socket > 0)
			close(game->soc.socket);
		free(game->keys);
		free(game->local_keys);
		free(game->fps);
		free(game);
	}
	if (IsWindowReady())
		CloseWindow();
}
