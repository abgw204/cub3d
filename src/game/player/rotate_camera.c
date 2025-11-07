/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:19:16 by gada-sil          #+#    #+#             */
/*   Updated: 2025/11/06 15:44:15 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static void    rotate_player(t_player *player, double rot_speed)
{
    player->angle += rot_speed;
    if (player->angle > 2 * PI)
        player->angle -= 2 * PI;
    else if (player->angle < 0)
        player->angle += 2 * PI;
    player->dir.x = cos(player->angle);
    player->dir.y = sin(player->angle);
    player->plane.x = -player->dir.y * FOV;
    player->plane.y =  player->dir.x * FOV;
}

void    rotate_camera_mouse(t_game *game, int middle, int x)
{
	if (x == middle)
		return ;
	if (x < middle)
		rotate_player(&game->player, -0.01 * (double)(middle - x) * g_delta_time);
	else
		rotate_player(&game->player, 0.01 * (double)(x - middle) * g_delta_time);
}

void    rotate_camera(t_game *game)
{
    if (game->keys[4] == '1')
        rotate_player(&game->player, -0.05);
    else if (game->keys[5] == '1')
        rotate_player(&game->player, 0.05);
}
