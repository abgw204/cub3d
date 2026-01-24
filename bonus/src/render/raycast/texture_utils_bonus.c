/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:54:32 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/24 15:39:49 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

t_image	*get_tex(double ray_dir_x, double ray_dir_y, int side, t_game *game)
{
	if (side == VERTICAL_WALL)
	{
		if (ray_dir_x > 0.0)
			return (&game->e);
		else
			return (&game->w);
	}
	else
	{
		if (ray_dir_y > 0.0)
			return (&game->s);
		else
			return (&game->n);
	}
	return (NULL);
}

void	draw_tex(t_image *screen, t_raycast r, t_texture t, int column)
{
	while (r.draw_start <= r.draw_end)
	{
		t.tex_y = (int)t.tex_pos % t.height;
		t.tex_pos += t.step;
		t.color = *(unsigned int *)(t.tex->addr + (t.tex_y * t.len)
				+ (t.tex_x * t.pitch));
		t.dst = screen->addr + r.draw_start * t.sc_line_len + column
			* t.sc_pitch;
		*(unsigned int *)t.dst = t.color;
		r.draw_start++;
	}
}

void	draw_door(t_image *screen, t_raycast r, t_texture t, int column)
{
	unsigned int	casing_color;

	while (r.draw_start <= r.draw_end)
	{
		t.tex_y = (int)t.tex_pos % t.height;
		t.tex_pos += t.step;
		t.color = *(unsigned int *)(t.tex->addr + ((t.tex_y) * t.len)
				+ ((t.tex_x + t.x_offset) * t.pitch));
		casing_color = *(unsigned int *)(t.tex->addr + ((t.tex_y) * t.len)
				+ (t.tex_x * t.pitch));
		if ((t.color & 0x00FFFFFF) != 0)
		{
			t.dst = screen->addr + r.draw_start * t.sc_line_len
				+ column * t.sc_pitch;
			*(unsigned int *)t.dst = t.color;
		}
		else if ((casing_color & 0x00FFFFFF) != 0)
		{
			t.dst = screen->addr + r.draw_start * t.sc_line_len
				+ column * t.sc_pitch;
			*(unsigned int *)t.dst = casing_color;
		}
		r.draw_start++;
	}
}

int	get_door_at(t_raycast *r, t_game *game)
{
	int	i;

	i = -1;
	while (++i < game->doors_n)
	{
		if (game->doors[i].pos.x == r->map_x
			&& game->doors[i].pos.y == r->map_y)
			return (game->doors[i].current_frame * (game->door.width / 6));
	}
	return (-1);
}
