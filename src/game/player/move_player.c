/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:18:14 by gada-sil          #+#    #+#             */
/*   Updated: 2025/11/06 15:44:23 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	move_w(t_game *game, t_player *player)
{
	double	new_x;
	double	new_y;

	new_x = player->pos.x + player->dir.x * player->speed * g_delta_time;
	new_y = player->pos.y + player->dir.y * player->speed * g_delta_time;
    if (game->map[(int)game->player.pos.y * game->map_w + (int)new_x] != '1')
		player->pos.x = new_x;
	if (game->map[(int)new_y * game->map_w + (int)player->pos.x] != '1')
		player->pos.y = new_y;
}

void	move_a(t_game *game, t_player *player)
{
	t_dv2	side;
	double	new_x;
	double	new_y;

    side.x = player->dir.y;
	side.y = -player->dir.x;
    new_x = player->pos.x + side.x * player->speed * g_delta_time;
    new_y = player->pos.y + side.y * player->speed * g_delta_time;
	if (game->map[(int)game->player.pos.y * game->map_w + (int)new_x] != '1')
		player->pos.x = new_x;
	if (game->map[(int)new_y * game->map_w + (int)player->pos.x] != '1')
		player->pos.y = new_y;
}

void	move_s(t_game *game, t_player *player)
{
	double	new_x;
	double	new_y;

	new_x = player->pos.x + -player->dir.x * player->speed * g_delta_time;
	new_y = player->pos.y + -player->dir.y * player->speed * g_delta_time;
    if (game->map[(int)game->player.pos.y * game->map_w + (int)new_x] != '1')
		player->pos.x = new_x;
	if (game->map[(int)new_y * game->map_w + (int)player->pos.x] != '1')
		player->pos.y = new_y;
}

void	move_d(t_game *game, t_player *player)
{
    t_dv2	side;
	double	new_x;
	double	new_y;

    side.x = -player->dir.y;
	side.y = player->dir.x;
    new_x = player->pos.x + side.x * player->speed * g_delta_time;
    new_y = player->pos.y + side.y * player->speed * g_delta_time;
	if (game->map[(int)game->player.pos.y * game->map_w + (int)new_x] != '1')
		player->pos.x = new_x;
	if (game->map[(int)new_y * game->map_w + (int)player->pos.x] != '1')
		player->pos.y = new_y;
}

void	move_player(t_game *game)
{
    t_player	*player;

    player = &game->player;

    if (game->keys[0] == '1')
        move_w(game, player);
    if (game->keys[1] == '1')
		move_a(game, player);
    if (game->keys[2] == '1')
		move_s(game, player);
    if (game->keys[3] == '1')
		move_d(game, player);
}
