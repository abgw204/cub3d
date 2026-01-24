/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:18:14 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/24 16:37:59 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	move_w(t_game *game, t_player *p)
{
	t_dv2	nw;
	t_dv2	coll;

	if (p->dir.x > 0.0)
		coll.x = COLLISION_DIST;
	else
		coll.x = -COLLISION_DIST;
	if (p->dir.y > 0.0)
		coll.y = COLLISION_DIST;
	else
		coll.y = -COLLISION_DIST;
	nw.x = p->pos.x + p->dir.x * p->speed * g_delta_time;
	nw.y = p->pos.y + p->dir.y * p->speed * g_delta_time;
	if (game->map[(int)p->pos.y * game->map_w + (int)(nw.x + coll.x)] != '1')
		p->pos.x = nw.x;
	if (game->map[(int)(nw.y + coll.y) *game->map_w + (int)p->pos.x] != '1')
		p->pos.y = nw.y;
}

void	move_a(t_game *game, t_player *p)
{
	t_dv2	side;
	t_dv2	nw;
	t_dv2	coll;

	if (-p->plane.x > 0.0)
		coll.x = COLLISION_DIST;
	else
		coll.x = -COLLISION_DIST;
	if (-p->plane.y > 0.0)
		coll.y = COLLISION_DIST;
	else
		coll.y = -COLLISION_DIST;
	side.x = p->dir.y;
	side.y = -p->dir.x;
	nw.x = p->pos.x + side.x * p->speed * g_delta_time;
	nw.y = p->pos.y + side.y * p->speed * g_delta_time;
	if (game->map[(int)p->pos.y * game->map_w + (int)(nw.x + coll.x)] != '1')
		p->pos.x = nw.x;
	if (game->map[(int)(nw.y + coll.y) *game->map_w + (int)p->pos.x] != '1')
		p->pos.y = nw.y;
}

void	move_s(t_game *game, t_player *p)
{
	t_dv2	nw;
	t_dv2	coll;

	if (p->dir.x > 0.0)
		coll.x = -COLLISION_DIST;
	else
		coll.x = COLLISION_DIST;
	if (p->dir.y > 0.0)
		coll.y = -COLLISION_DIST;
	else
		coll.y = COLLISION_DIST;
	nw.x = p->pos.x + -p->dir.x * p->speed * g_delta_time;
	nw.y = p->pos.y + -p->dir.y * p->speed * g_delta_time;
	if (game->map[(int)p->pos.y * game->map_w + (int)(nw.x + coll.x)] != '1')
		p->pos.x = nw.x;
	if (game->map[(int)(nw.y + coll.y) *game->map_w + (int)p->pos.x] != '1')
		p->pos.y = nw.y;
}

void	move_d(t_game *game, t_player *p)
{
	t_dv2	side;
	t_dv2	nw;
	t_dv2	coll;

	if (p->plane.x > 0.0)
		coll.x = COLLISION_DIST;
	else
		coll.x = -COLLISION_DIST;
	if (p->plane.y > 0.0)
		coll.y = COLLISION_DIST;
	else
		coll.y = -COLLISION_DIST;
	side.x = -p->dir.y;
	side.y = p->dir.x;
	nw.x = p->pos.x + side.x * p->speed * g_delta_time;
	nw.y = p->pos.y + side.y * p->speed * g_delta_time;
	if (game->map[(int)p->pos.y * game->map_w + (int)(nw.x + coll.x)] != '1')
		p->pos.x = nw.x;
	if (game->map[(int)(nw.y + coll.y) *game->map_w + (int)p->pos.x] != '1')
		p->pos.y = nw.y;
}

void	move_player(t_game *game)
{
	rotate_camera(game);
	if (game->keys[0] == '1')
		move_w(game, &game->player);
	if (game->keys[1] == '1')
		move_a(game, &game->player);
	if (game->keys[2] == '1')
		move_s(game, &game->player);
	if (game->keys[3] == '1')
		move_d(game, &game->player);
}
