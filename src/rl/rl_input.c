/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_input.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opencode                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19                                #+#    #+#             */
/*   Updated: 2026/04/19                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_rl.h"

static void	update_player_vectors(t_player *p)
{
	p->dir.x = cos(p->angle);
	p->dir.y = sin(p->angle);
	p->plane.x = -p->dir.y * FOV;
	p->plane.y = p->dir.x * FOV;
}

static void	apply_dead_inputs(t_game *game)
{
	game->keys[0] = '0';
	game->keys[1] = '0';
	game->keys[2] = '0';
	game->keys[3] = '0';
	game->local_keys[0] = '0';
	game->local_keys[1] = '0';
	game->keys[16] = '0';
	game->is_shooting = false;
}

static void	update_player_local(t_game *game)
{
	Vector2	md;

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
	if (game->local_keys[0] == '1')
		game->player.angle -= 2.5 * g_delta_time;
	else if (game->local_keys[1] == '1')
		game->player.angle += 2.5 * g_delta_time;
	if (game->local_keys[0] == '1' || game->local_keys[1] == '1')
		update_player_vectors(&game->player);
}

static void	apply_inputs_raylib(t_game *game)
{
	game->keys[0] = (IsKeyDown(KEY_W) ? '1' : '0');
	game->keys[1] = (IsKeyDown(KEY_A) ? '1' : '0');
	game->keys[2] = (IsKeyDown(KEY_S) ? '1' : '0');
	game->keys[3] = (IsKeyDown(KEY_D) ? '1' : '0');
	game->local_keys[0] = (IsKeyDown(KEY_LEFT) ? '1' : '0');
	game->local_keys[1] = (IsKeyDown(KEY_RIGHT) ? '1' : '0');
	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
		&& game->shoot_timer >= SHOOT_DELAY)
	{
		game->keys[16] = '1';
		game->shoot_timer = 0.0;
		game->is_shooting = true;
	}
}

void	rl_input_update(t_rl_ctx *ctx)
{
	t_game	*game;
	bool	dead;

	game = ctx->game;
	dead = (game->health <= 0);
	if (dead != ctx->prev_dead)
	{
		if (dead)
			EnableCursor();
		else
			DisableCursor();
		ctx->prev_dead = dead;
	}
	if (dead)
	{
		apply_dead_inputs(game);
		return;
	}
	apply_inputs_raylib(game);
	update_player_local(game);
}
