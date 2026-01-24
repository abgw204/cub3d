/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:39:15 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/24 16:31:32 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	raycast(t_game *game)
{
	t_raycast	raycast;
	int			start;
	int			limit;

	start = 0;
	limit = SCREEN_WIDTH - 1;
	while (start < limit)
	{
		cast_rays_and_draw(&raycast, game, start);
		start++;
	}
}
