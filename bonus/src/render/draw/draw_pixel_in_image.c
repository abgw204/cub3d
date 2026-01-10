/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel_in_image.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:52 by gada-sil          #+#    #+#             */
/*   Updated: 2025/12/19 12:48:22 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	draw_square(t_iv2 pos, int size, int color, t_image *image)
{
	char	*dst;
	int		i;
	int		j;

	i = pos.x;
	j = pos.y;
	while (i < pos.x + size)
	{
		while (j < pos.y + size)
		{
			dst = image->addr + (j++ * image->line_len + i * (image->bpp / 8));
			*(unsigned int*)dst = color;
		}
		j = pos.y;
		i++;
	}
}
