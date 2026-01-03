/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_door.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:39:15 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/02 19:45:10 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void    raycast_door(t_game *game)
{
	t_raycast	raycast;
	int			start;

	start = 0;
	while (start < SCREEN_WIDTH)
		cast_door_rays(&raycast, game, start++);
}
