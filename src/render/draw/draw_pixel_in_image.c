/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel_in_image.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:52 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/24 17:05:53 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	draw_circle(t_vector2 pos, int radius, int color, t_image *image)
{
	int	i;
	int	j;

	i = (int)pos.x - radius;
	j = (int)pos.y - radius;
	while (i < (int)pos.x + radius)
	{
		while (j < (int)pos.y + radius)
		{
			if ((pow(i - (int)pos.x, 2) + pow(j - (int)pos.y, 2)) <= pow(radius, 2))
				draw_pixel_in_image(image, i, j, color);
			j++;
		}
		j = (int)pos.y - radius;
		i++;
	}
}

void	draw_pixel_in_image(t_image *image, int x, int y, int color)
{
    char	*dst;

    dst = image->addr + (y * image->line_len + x * (image->bpp / 8));
    *(unsigned int*)dst = color;
}
