/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:18:14 by gada-sil          #+#    #+#             */
/*   Updated: 2025/11/05 02:21:58 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void    move_player(t_game *game)
{
    t_player	*player;
    t_dv2		side;

    player = &game->player;
    
    if (game->keys[0] == '1')
    {
        player->pos.x += player->dir.x * player->speed * g_delta_time;
        player->pos.y += player->dir.y * player->speed * g_delta_time;
    }
    if (game->keys[1] == '1')
    {
		side.x = player->dir.y;
		side.y = -player->dir.x;
        player->pos.x += side.x * player->speed * g_delta_time;
        player->pos.y += side.y * player->speed * g_delta_time;
    }
    if (game->keys[2] == '1')
    {
        player->pos.x += -player->dir.x * player->speed * g_delta_time;
        player->pos.y += -player->dir.y * player->speed * g_delta_time;
    }
    if (game->keys[3] == '1')
	{
		side.x = -player->dir.y;
		side.y = player->dir.x;
        player->pos.x += side.x * player->speed * g_delta_time;
        player->pos.y += side.y * player->speed * g_delta_time;
	}
}