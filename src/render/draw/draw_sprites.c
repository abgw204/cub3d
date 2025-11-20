/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:54:32 by gada-sil          #+#    #+#             */
/*   Updated: 2025/11/07 08:29:15 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	draw_sprites(t_game *game)
{
	for (int i = 0; i < 1920; i++)
		printf("%.4f\n", game->z_buffer[i]);
	//static double	x = 5.5;
	//static double	y = 5.5;
	//t_player		*player;
	//t_dv2			sprite;
	//double			inv_det;

	//player = (t_player *)&game->player;
//	sprite.x = x - player->pos.x;
//	sprite.y = y - player->pos.y;
	//inv_det = 1.0 / (player->plane_x * player->dir.y
	//				- player->plane_y * player->dir.y)
}
