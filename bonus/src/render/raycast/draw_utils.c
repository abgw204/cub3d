/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 10:44:12 by gada-sil          #+#    #+#             */
/*   Updated: 2025/12/10 10:45:16 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	draw_ceiling(t_raycast *r, t_image *screen, int start, int limit)
{
	char	*dst;
	int		i;
	int		line_len;
	int		pitch;
	int		color;

	dst = NULL;
	i = -1;
	line_len = screen->line_len;
	pitch = screen->bpp >> 3;
	color = r->c_color;
	while (++i < limit)
	{
		dst = screen->addr
			+ i * line_len
			+ start * pitch;
		*(unsigned int *)dst = color;
	}
}

void	draw_floor(t_raycast *r, t_image *screen, int start, int limit)
{
	char	*dst;
	int		i;
	int		line_len;
	int		pitch;
	int		color;

	dst = NULL;
	i = r->draw_end - 1;
	line_len = screen->line_len;
	pitch = screen->bpp >> 3;
	color = r->f_color;
	while (++i < limit)
	{
		dst = screen->addr
			+ i * line_len
			+ start * pitch;
		*(unsigned int *)dst = color;
	}
}