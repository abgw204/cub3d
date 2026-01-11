/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_camera.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:19:16 by gada-sil          #+#    #+#             */
/*   Updated: 2025/12/12 11:36:19 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static void    rotate_player(t_player *player, double rot_speed)
{
    player->angle += rot_speed * g_delta_time;
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
	if (x < middle)
		rotate_player(&game->player, -0.03 * (double)(middle - x));
	else if (x > middle)
		rotate_player(&game->player, 0.03 * (double)(x - middle));
}

void    rotate_camera(t_game *game)
{
    if (game->local_keys[0] == '1')
        rotate_player(&game->player, -3.0);
    else if (game->local_keys[1] == '1')
		rotate_player(&game->player, 3.0);
}
