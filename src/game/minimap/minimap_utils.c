/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 03:33:10 by gada-sil          #+#    #+#             */
/*   Updated: 2025/11/05 03:45:25 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	init_mini(t_minimap *mini, t_game *game)
{
	mini->pos.x = 0;
	mini->pos.y = 0;
	mini->x_bg = (int)game->player.pos.x - 5;
	mini->y_bg = (int)game->player.pos.y - 5;
	mini->x_end = (int)game->player.pos.x + 5;
	mini->y_end = (int)game->player.pos.y + 5;
	clear_minimap(&mini->img);
}

int	in_bounds(int x, int y, int endx, int endy)
{
	return (x >= 0 && y >= 0 && x < endx && y < endy);
}

void	clear_minimap(t_image *minimap)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < minimap->height)
	{
		while (++j < minimap->width)
			draw_pixel_in_image(minimap, j, i, 0x005500);
		j = -1;
	}
}
