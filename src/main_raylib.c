/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_raylib.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opencode                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/18                                #+#    #+#             */
/*   Updated: 2026/04/18                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// raylib renderer path (GPU) used during migration.
// This binary intentionally does not link MiniLibX and avoids the threaded
// CPU renderer: we render the scene using GPU textured quads.

#include "../include/cub3d.h"

#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <arpa/inet.h>
#include <sys/socket.h>

#include "raylib.h"

// cub3d core helpers normally live in src/main.c + src/error/error.c.
// For the raylib binary we provide minimal, MLX-free implementations here.

t_data	*get_data(void)
{
	static t_data	data_cub;

	return (&data_cub);
}

int	print_error(char *error_message)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(error_message, 2);
	return (1);
}

int	print_perror(void)
{
	ft_putendl_fd("Error", 2);
	perror("cub3d");
	return (1);
}

static bool	str_ends_with(const char *s, const char *suffix)
{
	size_t	ls;
	size_t	lx;

	if (!s || !suffix)
		return (false);
	ls = strlen(s);
	lx = strlen(suffix);
	if (lx > ls)
		return (false);
	return (memcmp(s + (ls - lx), suffix, lx) == 0);
}

static Texture2D	load_texture_any(const char *path)
{
	Texture2D	tex;
	char		png_path[512];
	char		name[256];
	const char	*base;
	size_t		len;

	tex = LoadTexture(path);
	if (tex.id != 0)
		return (tex);
	// raylib's default image loader does not support .xpm; try a project-local
	// png mirror under res/textures_png/<name>.png.
	if (!str_ends_with(path, ".xpm"))
		return (tex);
	base = strrchr(path, '/');
	base = (base == NULL) ? path : base + 1;
	len = strlen(base);
	if (len < 5)
		return (tex);
	len -= 4;
	if (len >= sizeof(name))
		len = sizeof(name) - 1;
	memcpy(name, base, len);
	name[len] = '\0';
	snprintf(png_path, sizeof(png_path), "res/textures_png/%s.png", name);
	return (LoadTexture(png_path));
}

typedef struct s_rl_tex
{
	Texture2D	n;
	Texture2D	s;
	Texture2D	e;
	Texture2D	w;
} t_rl_tex;

typedef struct s_rl_sprite_ref
{
	int		idx;
	double	depth;
} 	t_rl_sprite_ref;

typedef struct s_gun_anim
{
	int	frame;
	float	acc;
} 	t_gun_anim;

#ifndef CUB3D_RL_RENDER_SCALE
// Render scale < 1.0 reduces CPU DDA work + draw calls, then upscales via GPU.
// 0.5 is a good default for fullscreen performance.
# define CUB3D_RL_RENDER_SCALE 0.5f
#endif

static int	clampi(int v, int lo, int hi)
{
	if (v < lo)
		return (lo);
	if (v > hi)
		return (hi);
	return (v);
}

static RenderTexture2D	create_scene_target(int screen_w, int screen_h)
{
	int	w;
	int	h;

	w = (int)((float)screen_w * CUB3D_RL_RENDER_SCALE);
	h = (int)((float)screen_h * CUB3D_RL_RENDER_SCALE);
	// Avoid tiny targets on very small windows.
	w = clampi(w, 320, screen_w);
	h = clampi(h, 180, screen_h);
	return (LoadRenderTexture(w, h));
}

static void	set_null(t_game *game)
{
	memset(game, 0, sizeof(*game));
	game->fps = NULL;
	game->keys = NULL;
	game->local_keys = NULL;
	game->map = NULL;
	game->z_buffer = NULL;
}

static void	init_config(t_config *config)
{
	// Keep the legacy FPS string code disabled; raylib can draw FPS directly.
	config->show_fps = 0;
	config->show_mouse = true;
}

static Color	color_from_hex_rgb(int hex)
{
	Color	c;

	// Our parser stores colors in 0xRRGGBB format.
	c.r = (unsigned char)((hex >> 16) & 0xFF);
	c.g = (unsigned char)((hex >> 8) & 0xFF);
	c.b = (unsigned char)(hex & 0xFF);
	c.a = 255;
	return (c);
}

static void	draw_textured_column(Texture2D tex, int x,
		int orig_start, int line_height, int y0, int y1, int tex_x)
{
	Rectangle src;
	Rectangle dst;
	float		tex_y0;
	float		tex_h;

	if (y1 <= y0)
		return;
	// Sample a 1px-wide vertical slice from the texture.
	// If the wall is clipped (draw_start/end), adjust the source Y range.
	tex_y0 = ((float)(y0 - orig_start) / (float)line_height) * (float)tex.height;
	tex_h = ((float)(y1 - y0) / (float)line_height) * (float)tex.height;
	if (tex_y0 < 0.0f)
		tex_y0 = 0.0f;
	if (tex_y0 + tex_h > (float)tex.height)
		tex_h = (float)tex.height - tex_y0;

	src.x = (float)tex_x;
	src.y = tex_y0;
	src.width = 1.0f;
	src.height = tex_h;

	dst.x = (float)x;
	dst.y = (float)y0;
	dst.width = 1.0f;
	dst.height = (float)(y1 - y0);

	DrawTexturePro(tex, src, dst, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);
}

static void	fix_sprite_boundaries_rl(t_sprite *sp, int screen_w, int screen_h)
{
	if (sp->end_x >= screen_w)
		sp->end_x = screen_w - 1;
	if (sp->end_y >= screen_h)
		sp->end_y = screen_h - 1;
	if (sp->start_x < 0)
		sp->start_x = 0;
	if (sp->start_y < 0)
		sp->start_y = 0;
}

static void	calculate_sprites_size_rl(t_game *game, int screen_w, int screen_h)
{
	t_players	*p;
	int			i;

	p = game->players;
	for (i = 0; i < MAX_PLAYERS; i++)
	{
		if (p[i].id == game->my_id || !p[i].connected)
			continue;
		p[i].sp.x = p[i].x - game->player.pos.x;
		p[i].sp.y = p[i].y - game->player.pos.y;
		p[i].sp.inv_det = 1.0 / (game->player.plane.x * game->player.dir.y
						- game->player.dir.x * game->player.plane.y);
		p[i].sp.transform_x = p[i].sp.inv_det
			* (game->player.dir.y * p[i].sp.x - game->player.dir.x * p[i].sp.y);
		p[i].sp.transform_y = p[i].sp.inv_det
			* (-game->player.plane.y * p[i].sp.x + game->player.plane.x * p[i].sp.y);
		p[i].sp.screen_x = (int)(((double)screen_w / 2.0)
					* (1.0 + p[i].sp.transform_x / p[i].sp.transform_y));
		p[i].sp.height = abs((int)((double)screen_h / p[i].sp.transform_y));
		p[i].sp.width = p[i].sp.height;
		p[i].sp.start_y = -p[i].sp.height / 2 + screen_h / 2;
		p[i].sp.end_y = p[i].sp.height / 2 + screen_h / 2;
		p[i].sp.start_x = -p[i].sp.width / 2 + p[i].sp.screen_x;
		p[i].sp.end_x = p[i].sp.width / 2 + p[i].sp.screen_x;
		fix_sprite_boundaries_rl(&p[i].sp, screen_w, screen_h);
	}
}

static int	cmp_depth_desc(const void *a, const void *b)
{
	const t_rl_sprite_ref	*sa;
	const t_rl_sprite_ref	*sb;

	sa = (const t_rl_sprite_ref *)a;
	sb = (const t_rl_sprite_ref *)b;
	if (sa->depth < sb->depth)
		return (1);
	if (sa->depth > sb->depth)
		return (-1);
	return (0);
}

static void	draw_enemy_sprites_gpu(t_game *game, Texture2D enemy, int screen_w, int screen_h)
{
	t_rl_sprite_ref	refs[MAX_PLAYERS];
	int				count;
	int				i;

	if (enemy.id == 0 || game->z_buffer == NULL)
		return;
	calculate_sprites_size_rl(game, screen_w, screen_h);
	count = 0;
	for (i = 0; i < MAX_PLAYERS; i++)
	{
		if (game->players[i].id == game->my_id || !game->players[i].connected)
			continue;
		// Don't render dead players: they are in respawn screen.
		if (game->players[i].health <= 0)
			continue;
		// Behind the camera or too close to project safely.
		if (game->players[i].sp.transform_y <= 0.0001)
			continue;
		refs[count].idx = i;
		refs[count].depth = game->players[i].sp.transform_y;
		count++;
	}
	if (count <= 0)
		return;
	qsort(refs, (size_t)count, sizeof(refs[0]), cmp_depth_desc);
	for (int ri = 0; ri < count; ri++)
	{
		t_sprite	sp;
		int		orig_start;
		int		y0;
		int		y1;

		sp = game->players[refs[ri].idx].sp;
		orig_start = -sp.height / 2 + screen_h / 2;
		y0 = sp.start_y;
		y1 = sp.end_y;
		if (y0 < 0)
			y0 = 0;
		if (y1 >= screen_h)
			y1 = screen_h - 1;
		if (sp.end_x < 0 || sp.start_x >= screen_w)
			continue;
		for (int stripe = sp.start_x; stripe < sp.end_x; stripe++)
		{
			int	tex_x;

			if (stripe < 0 || stripe >= screen_w)
				continue;
			if (sp.transform_y >= game->z_buffer[stripe])
				continue;
			tex_x = (int)(((double)(stripe - (-sp.width / 2 + sp.screen_x))
					* (double)enemy.width) / (double)sp.width);
			if (tex_x < 0)
				tex_x = 0;
			if (tex_x >= enemy.width)
				tex_x = enemy.width - 1;
			draw_textured_column(enemy, stripe, orig_start, sp.height, y0, y1, tex_x);
		}
	}
}

static bool	draw_gun_hud(Texture2D sheet, int screen_w, int screen_h, t_gun_anim *anim, bool shooting)
{
	const int	frames = 5;
	// Animation speed for the gun spritesheet.
	const float	fps = 53.0f;
	int			frame_w;
	int			frame_h;
	Rectangle	src;
	Rectangle	dst;
	float		scale;
	bool		finished;

	finished = false;
	if (sheet.id == 0)
		return (false);
	frame_w = sheet.width / frames;
	frame_h = sheet.height;
	if (frame_w <= 0 || frame_h <= 0)
		return (false);
	// Advance frames only while shooting.
	if (shooting)
	{
		anim->acc += (float)g_delta_time;
		while (anim->acc >= (1.0f / fps))
		{
			anim->acc -= (1.0f / fps);
			anim->frame++;
			if (anim->frame >= frames)
			{
				anim->frame = 0;
				anim->acc = 0.0f;
				finished = true;
				break;
			}
		}
	}

	src.x = (float)(anim->frame * frame_w);
	src.y = 0.0f;
	src.width = (float)frame_w;
	src.height = (float)frame_h;

	// Draw centered, slightly below crosshair.
	scale = (float)screen_w / 1920.0f;
	if (scale < 0.75f)
		scale = 0.75f;
	if (scale > 1.25f)
		scale = 1.25f;
	// Legacy MLX draw_sprite_scaled anchor: top-left at (SCREEN_W/2, SCREEN_H/2 - 50)
	scale = 5.0f * scale;
	dst.width = (float)frame_w * scale;
	dst.height = (float)frame_h * scale;
	dst.x = (float)screen_w / 2.0f;
	dst.y = (float)screen_h / 2.0f - 50.0f * (scale / 5.0f);

	DrawTexturePro(sheet, src, dst, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);
	return (finished);
}

static int	update_all_players_from_packet(t_game *game, char *buffer, int latest_bytes)
{
	int	offset;
	int	id;
	int	connected;
	int	health;
	double	x;
	double	y;
	int	i;

	offset = 0;
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		if (offset + SEND_PACKET_SIZE > latest_bytes)
			break;
		memcpy(&connected, buffer + offset + 20, sizeof(int));
		if (!connected)
		{
			game->players[i].connected = 0;
			game->players[i].id = -1;
			offset += SEND_PACKET_SIZE;
			continue;
		}
		memcpy(&id, buffer + offset, sizeof(int));
		memcpy(&x, buffer + offset + 4, sizeof(double));
		memcpy(&y, buffer + offset + 12, sizeof(double));
		memcpy(&health, buffer + offset + 24, sizeof(int));

		game->players[i].connected = connected;
		game->players[i].id = id;
		game->players[i].x = x;
		game->players[i].y = y;
		game->players[i].health = health;
		if (id == game->my_id)
		{
			game->player.pos.x = x;
			game->player.pos.y = y;
			game->health = health;
		}
		offset += SEND_PACKET_SIZE;
	}
	return (0);
}

static void	receive_server_state(t_game *game)
{
	char	tmp_buffer[MAX_PLAYERS * SEND_PACKET_SIZE];
	char	latest_buffer[MAX_PLAYERS * SEND_PACKET_SIZE];
	int		bytes;
	int		latest_bytes;

	bytes = 1;
	latest_bytes = 0;
	while (bytes > 0)
	{
		bytes = recvfrom(game->soc.socket, tmp_buffer, sizeof(tmp_buffer), 0,
			(struct sockaddr *)&game->soc.peer, &game->soc.peer_len);
		if (bytes > 0 && bytes <= (int)sizeof(tmp_buffer))
		{
			memcpy(latest_buffer, tmp_buffer, bytes);
			latest_bytes = bytes;
		}
	}
	if (latest_bytes <= 0)
		return;
	update_all_players_from_packet(game, latest_buffer, latest_bytes);
}

static void	update_player_vectors(t_player *p)
{
	p->dir.x = cos(p->angle);
	p->dir.y = sin(p->angle);
	p->plane.x = -p->dir.y * FOV;
	p->plane.y = p->dir.x * FOV;
}

static void	update_player_local(t_game *game)
{
	// Mouse look.
	Vector2 md;

	md = GetMouseDelta();
	if (fabs(md.x) > 0.0f)
	{
		game->player.angle += (double)md.x * (0.0025 / 3.0);
		if (game->player.angle > 2 * PI)
			game->player.angle -= 2 * PI;
		else if (game->player.angle < 0)
			game->player.angle += 2 * PI;
		update_player_vectors(&game->player);
	}
	// Keyboard rotation.
	if (game->local_keys[0] == '1')
		game->player.angle -= 2.5 * g_delta_time;
	else if (game->local_keys[1] == '1')
		game->player.angle += 2.5 * g_delta_time;
	if (game->local_keys[0] == '1' || game->local_keys[1] == '1')
		update_player_vectors(&game->player);
	// Movement is authoritative on the server.
}

static void	apply_dead_inputs(t_game *game)
{
	// Keep sending packets (so the server keeps broadcasting to us),
	// but don't allow any movement/rotation/shoot while dead.
	game->keys[0] = '0';
	game->keys[1] = '0';
	game->keys[2] = '0';
	game->keys[3] = '0';
	game->local_keys[0] = '0';
	game->local_keys[1] = '0';
	game->keys[16] = '0';
	game->is_shooting = false;
}

static bool	draw_death_overlay(int screen_w, int screen_h)
{
	const char	*title;
	const char	*btn;
	int			title_sz;
	int			btn_sz;
	int			tw;
	int			x;
	int			y;
	Rectangle	btn_rect;
	Vector2		m;
	bool		hover;

	// Slight red tint over the current frame.
	DrawRectangle(0, 0, screen_w, screen_h, (Color){ 210, 35, 35, 60 });

	title = "You died";
	btn = "Respawn";
	title_sz = 64;
	btn_sz = 28;

	tw = MeasureText(title, title_sz);
	x = screen_w / 2 - tw / 2;
	y = screen_h / 2 - 150;
	DrawText(title, x, y, title_sz, RAYWHITE);

	btn_rect.width = 260.0f;
	btn_rect.height = 62.0f;
	btn_rect.x = (float)screen_w / 2.0f - btn_rect.width / 2.0f;
	btn_rect.y = (float)screen_h / 2.0f - btn_rect.height / 2.0f + 10.0f;

	m = GetMousePosition();
	hover = CheckCollisionPointRec(m, btn_rect);
	DrawRectangleRounded(btn_rect, 0.25f, 10, (Color){ 22, 22, 26, 235 });
	DrawRectangleLinesEx(btn_rect, 2,
		hover ? (Color){ 245, 245, 255, 220 } : (Color){ 180, 180, 190, 160 });
	{
		int bw = MeasureText(btn, btn_sz);
		DrawText(btn,
			(int)(btn_rect.x + btn_rect.width / 2.0f - (float)bw / 2.0f),
			(int)(btn_rect.y + btn_rect.height / 2.0f - (float)btn_sz / 2.0f),
			btn_sz,
			hover ? RAYWHITE : (Color){ 215, 215, 225, 220 });
	}
	return (hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
}

static void	draw_walls_gpu(t_game *game, t_rl_tex *t, int screen_w, int screen_h)
{
	int		x;
	double	camera_x;
	double	camera_step;

	camera_x = -1.0;
	camera_step = 2.0 / (double)screen_w;
	for (x = 0; x < screen_w; x++)
	{
		double	ray_dir_x;
		double	ray_dir_y;
		int		map_x;
		int		map_y;
		double	delta_dist_x;
		double	delta_dist_y;
		double	side_dist_x;
		double	side_dist_y;
		int		step_x;
		int		step_y;
		int		hit;
		int		side;
		double	perp_wall_dist;
		int		line_height;
		int		orig_start;
		int		orig_end;
		int		draw_start;
		int		draw_end;
		double	wall_x;
		int		tex_x;
		Texture2D	tex;

		ray_dir_x = game->player.dir.x + game->player.plane.x * camera_x;
		ray_dir_y = game->player.dir.y + game->player.plane.y * camera_x;
		map_x = (int)game->player.pos.x;
		map_y = (int)game->player.pos.y;

		// Avoid division by zero.
		delta_dist_x = (ray_dir_x == 0.0) ? 1e30 : fabs(1.0 / ray_dir_x);
		delta_dist_y = (ray_dir_y == 0.0) ? 1e30 : fabs(1.0 / ray_dir_y);

		if (ray_dir_x < 0.0)
		{
			step_x = -1;
			side_dist_x = (game->player.pos.x - (double)map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = ((double)map_x + 1.0 - game->player.pos.x) * delta_dist_x;
		}
		if (ray_dir_y < 0.0)
		{
			step_y = -1;
			side_dist_y = (game->player.pos.y - (double)map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = ((double)map_y + 1.0 - game->player.pos.y) * delta_dist_y;
		}

		hit = 0;
		side = 0;
		while (!hit)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (map_x < 0 || map_y < 0 || map_x >= game->map_w || map_y >= game->map_h)
			{
				hit = 1;
				break;
			}
			if (game->map[map_y * game->map_w + map_x] == '1')
				hit = 1;
		}

		if (side == 0)
			perp_wall_dist = side_dist_x - delta_dist_x;
		else
			perp_wall_dist = side_dist_y - delta_dist_y;
		if (perp_wall_dist < 0.0001)
			perp_wall_dist = 0.0001;

		line_height = (int)((double)screen_h / perp_wall_dist);
		orig_start = -line_height / 2 + screen_h / 2;
		orig_end = line_height / 2 + screen_h / 2;
		draw_start = orig_start;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = orig_end;
		if (draw_end >= screen_h)
			draw_end = screen_h - 1;

		// Pick texture and compute texture x coordinate.
		if (side == 0)
		{
			wall_x = game->player.pos.y + perp_wall_dist * ray_dir_y;
			if (ray_dir_x > 0.0)
				tex = t->w;
			else
				tex = t->e;
		}
		else
		{
			wall_x = game->player.pos.x + perp_wall_dist * ray_dir_x;
			if (ray_dir_y > 0.0)
				tex = t->n;
			else
				tex = t->s;
		}
		wall_x -= floor(wall_x);
		tex_x = (int)(wall_x * (double)tex.width);
		if (tex_x < 0)
			tex_x = 0;
		if (tex_x >= tex.width)
			tex_x = tex.width - 1;

		draw_textured_column(tex, x, orig_start, line_height, draw_start, draw_end, tex_x);
		if (game->z_buffer != NULL)
			game->z_buffer[x] = perp_wall_dist;
		camera_x += camera_step;
	}
}

static void	apply_inputs_raylib(t_game *game)
{
	// Movement keys (network packet) use W/A/S/D.
	game->keys[0] = (IsKeyDown(KEY_W) ? '1' : '0');
	game->keys[1] = (IsKeyDown(KEY_A) ? '1' : '0');
	game->keys[2] = (IsKeyDown(KEY_S) ? '1' : '0');
	game->keys[3] = (IsKeyDown(KEY_D) ? '1' : '0');
	game->local_keys[0] = (IsKeyDown(KEY_LEFT) ? '1' : '0');
	game->local_keys[1] = (IsKeyDown(KEY_RIGHT) ? '1' : '0');
	// Shot: server expects a one-frame '1' at keys[16].
	// Gate it client-side to avoid spamming (legacy SHOOT_DELAY behavior).
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
		&& game->shoot_timer >= SHOOT_DELAY)
	{
		game->keys[16] = '1';
		game->shoot_timer = 0.0;
		game->is_shooting = true;
	}
}

static int	close_fd_ok(int fd)
{
	close(fd);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_rl_tex	tex;
	Texture2D	enemy;
	Texture2D	gun;
	Sound		gunshot;
	bool		audio_ok;
	t_gun_anim	gun_anim;
	bool		dead;
	bool		want_respawn;
	bool		prev_dead;
	RenderTexture2D	scene;
	int					want_w;
	int					want_h;
	int		idx_no;
	int		idx_so;
	int		idx_we;
	int		idx_ea;
	int		map_fd;

	if (argc != 3)
		return (print_error("Usage: ./cub3d_rl <MAP_PATH> <ID>"));
	// Parse map/config.
	map_fd = open(argv[1], O_RDONLY);
	if (map_fd < 0)
		return (print_perror());
	if (parse_given_fd(map_fd))
		return (close_fd_ok(map_fd) || 1);
	close_fd_ok(map_fd);
	set_null(&game);
	game.data = get_data();
	game.map = game.data->map;
	game.map_w = game.data->map_w;
	game.map_h = game.data->map_h;
	get_player_info(&game);
	init_config(&game.config);

	game.keys = ft_calloc(1, 17);
	game.local_keys = ft_calloc(1, 3);
	if (!game.keys || !game.local_keys)
		return (print_error("Memory allocation error"));
	ft_memset(game.keys, '0', 17);
	ft_memset(game.local_keys, '0', 3);

	game.my_id = atoi(argv[2]);
	memcpy(game.keys + 4, &game.my_id, sizeof(int));
	game.player.speed = 2.0f;
	game.health = 3;
	game.soc.socket = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
	if (game.soc.socket == -1)
		return (print_perror());
	memset(&game.soc.peer, 0, sizeof(game.soc.peer));
	game.soc.peer.sin_family = AF_INET;
	game.soc.peer.sin_port = htons(5000);
	inet_pton(AF_INET, "127.0.0.1", &game.soc.peer.sin_addr);
	game.soc.peer_len = sizeof(game.soc.peer);
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		game.players[i].connected = 0;
		game.players[i].id = -1;
		game.players[i].health = 0;
	}

	// Uncapped frame loop for migration performance testing.
	// (VSync often locks to 60Hz on many setups.)
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(1920, 1080, "cub3d (raylib)");
	{
		int monitor = GetCurrentMonitor();
		int mw = GetMonitorWidth(monitor);
		int mh = GetMonitorHeight(monitor);
		ToggleFullscreen();
		SetWindowSize(mw, mh);
	}
	SetTargetFPS(0);
	DisableCursor();
	// Audio is optional; keep the game running if it fails.
	audio_ok = false;
	gunshot = (Sound){0};
	InitAudioDevice();
	if (IsAudioDeviceReady())
	{
		audio_ok = true;
		gunshot = LoadSound("res/sounds/gunshot.mp3");
		if (gunshot.frameCount == 0)
			audio_ok = false;
		else
			SetSoundVolume(gunshot, 0.6f);
	}
	scene = create_scene_target(GetScreenWidth(), GetScreenHeight());
	// Scaling filter: POINT is faster and crisp; switch to BILINEAR if you prefer.
	SetTextureFilter(scene.texture, TEXTURE_FILTER_POINT);
	game.screen_w = scene.texture.width;
	game.screen_h = scene.texture.height;
	game.z_buffer = (double *)malloc((size_t)game.screen_w * sizeof(double));
	if (game.z_buffer == NULL)
	{
		CloseWindow();
		return (print_error("Memory allocation error (z_buffer)"));
	}

	// Load textures directly on GPU.
	idx_no = -1;
	idx_so = -1;
	idx_we = -1;
	idx_ea = -1;
	for (int i = 0; game.data->config[i]; i++)
	{
		if (!ft_strcmp(game.data->config[i][0], "NO")) idx_no = i;
		else if (!ft_strcmp(game.data->config[i][0], "SO")) idx_so = i;
		else if (!ft_strcmp(game.data->config[i][0], "WE")) idx_we = i;
		else if (!ft_strcmp(game.data->config[i][0], "EA")) idx_ea = i;
	}
	if (idx_no < 0 || idx_so < 0 || idx_we < 0 || idx_ea < 0)
	{
		CloseWindow();
		return (print_error("Invalid config: missing one or more texture paths"));
	}
	tex.n = load_texture_any(game.data->config[idx_no][1]);
	tex.s = load_texture_any(game.data->config[idx_so][1]);
	tex.w = load_texture_any(game.data->config[idx_we][1]);
	tex.e = load_texture_any(game.data->config[idx_ea][1]);
	enemy = LoadTexture("res/textures_png/sprites/enemy.png");
	gun = LoadTexture("res/textures_png/sprites/gun_spritesheet.png");
	gun_anim.frame = 0;
	gun_anim.acc = 0.0f;
	want_respawn = false;
	prev_dead = false;
	if (tex.n.id == 0 || tex.s.id == 0 || tex.w.id == 0 || tex.e.id == 0)
	{
		if (tex.n.id == 0)
			fprintf(stderr, "raylib texture load failed: NO=%s\n", game.data->config[idx_no][1]);
		if (tex.s.id == 0)
			fprintf(stderr, "raylib texture load failed: SO=%s\n", game.data->config[idx_so][1]);
		if (tex.w.id == 0)
			fprintf(stderr, "raylib texture load failed: WE=%s\n", game.data->config[idx_we][1]);
		if (tex.e.id == 0)
			fprintf(stderr, "raylib texture load failed: EA=%s\n", game.data->config[idx_ea][1]);
		CloseWindow();
		return (print_error("Failed to load one or more textures via raylib"));
	}

	while (!WindowShouldClose())
	{
		set_delta_time(&game);
		game.shoot_timer += g_delta_time;
		// Reset one-frame actions.
		game.keys[16] = '0';
		dead = (game.health <= 0);
		// Only toggle cursor on state changes; doing it every frame breaks GetMouseDelta().
		if (dead != prev_dead)
		{
			if (dead)
				EnableCursor();
			else
				DisableCursor();
			prev_dead = dead;
		}
		if (dead)
		{
			apply_dead_inputs(&game);
			// Keep view frozen while dead.
		}
		else
		{
			apply_inputs_raylib(&game);
			// If a shot happened this frame, restart the gun animation.
			if (game.keys[16] == '1')
			{
				gun_anim.frame = 0;
				gun_anim.acc = 0.0f;
				if (audio_ok)
					PlaySound(gunshot);
			}
			update_player_local(&game);
		}
		memcpy(game.keys + 8, &game.player.angle, sizeof(double));
		if (dead && want_respawn)
		{
			// Respawn request piggybacks on the 1-byte field used for shots.
			// Server treats only '1' as shot; '2' is respawn.
			game.keys[16] = '2';
			want_respawn = false;
		}
		// Send authoritative input packet to server (same 17-byte format).
		(void)sendto(game.soc.socket, game.keys, 17, 0,
			(struct sockaddr *)&game.soc.peer, sizeof(game.soc.peer));
		receive_server_state(&game);
		free(game.fps);
		game.fps = NULL;

		if (IsWindowResized())
		{
			want_w = (int)((float)GetScreenWidth() * CUB3D_RL_RENDER_SCALE);
			want_h = (int)((float)GetScreenHeight() * CUB3D_RL_RENDER_SCALE);
			want_w = clampi(want_w, 320, GetScreenWidth());
			want_h = clampi(want_h, 180, GetScreenHeight());
			if (want_w != scene.texture.width || want_h != scene.texture.height)
			{
				UnloadRenderTexture(scene);
				scene = LoadRenderTexture(want_w, want_h);
				SetTextureFilter(scene.texture, TEXTURE_FILTER_POINT);
				game.screen_w = scene.texture.width;
				game.screen_h = scene.texture.height;
				free(game.z_buffer);
				game.z_buffer = (double *)malloc((size_t)game.screen_w * sizeof(double));
				if (game.z_buffer == NULL)
				{
					// Can't safely render without z-buffer for sprite occlusion.
					CloseWindow();
					return (print_error("Memory allocation error (z_buffer resize)"));
				}
			}
		}

		BeginTextureMode(scene);
		{
			int iw = scene.texture.width;
			int ih = scene.texture.height;
			Color ceil_c = color_from_hex_rgb(game.data->c_color);
			Color floor_c = color_from_hex_rgb(game.data->f_color);
			DrawRectangle(0, 0, iw, ih / 2, ceil_c);
			DrawRectangle(0, ih / 2, iw, ih - (ih / 2), floor_c);
			draw_walls_gpu(&game, &tex, iw, ih);
			draw_enemy_sprites_gpu(&game, enemy, iw, ih);
		}
		EndTextureMode();

		BeginDrawing();
		ClearBackground((Color){ 18, 18, 20, 255 });
		{
			Rectangle src = { 0.0f, 0.0f, (float)scene.texture.width, -(float)scene.texture.height };
			Rectangle dst = { 0.0f, 0.0f, (float)GetScreenWidth(), (float)GetScreenHeight() };
			DrawTexturePro(scene.texture, src, dst, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);
		}
		// HUD pass (not affected by render scale).
		if (!dead)
		{
			if (draw_gun_hud(gun, GetScreenWidth(), GetScreenHeight(), &gun_anim, game.is_shooting))
				game.is_shooting = false;
		}
		else
		{
			if (draw_death_overlay(GetScreenWidth(), GetScreenHeight()))
				want_respawn = true;
		}
		DrawFPS(20, 20);
		EndDrawing();
	}

	UnloadRenderTexture(scene);
	UnloadTexture(tex.n);
	UnloadTexture(tex.s);
	UnloadTexture(tex.w);
	UnloadTexture(tex.e);
	if (enemy.id != 0)
		UnloadTexture(enemy);
	if (gun.id != 0)
		UnloadTexture(gun);
	if (audio_ok)
		UnloadSound(gunshot);
	if (IsAudioDeviceReady())
		CloseAudioDevice();
	free(game.z_buffer);
	close(game.soc.socket);
	CloseWindow();
	return (0);
}
