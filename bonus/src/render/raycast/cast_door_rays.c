/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_door_rays.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:54:32 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/02 19:44:44 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	draw_door(t_image *screen, t_raycast r, t_door_tex t, int column)
{
	unsigned int	casing_color;

	while (r.draw_start <= r.draw_end)
    {
	    t.tex_y = (int)t.tex_pos % t.height;
	    t.tex_pos += t.step;
	    t.color = *(unsigned int *)(t.tex->addr + ((t.tex_y - 1) * t.len)
				+ ((t.tex_x + t.x_offset) * t.pitch));
		casing_color = *(unsigned int *)(t.tex->addr + ((t.tex_y - 1) * t.len)
				+ (t.tex_x * t.pitch));
		if ((t.color & 0x00FFFFFF) != 0)
		{
			t.dst = screen->addr + r.draw_start * t.sc_line_len + column * t.sc_pitch;
			*(unsigned int *)t.dst = t.color;
		}
		else if ((casing_color & 0x00FFFFFF) != 0)
		{
			t.dst = screen->addr + r.draw_start * t.sc_line_len + column * t.sc_pitch;
			*(unsigned int *)t.dst = casing_color;
		}
        r.draw_start++;
    }
}

int	get_door_at(t_raycast *r, t_game *game)
{
	unsigned int	i;

	i = -1;
	while (++i < game->doors_n)
	{
		if (game->doors[i].pos.x == r->map_x
			&& game->doors[i].pos.y == r->map_y)
			return (game->doors[i].current_frame * (game->door.width / 6));
	}
	return (-1);
}

static void    draw_column(t_image *screen, t_raycast r, int col, t_game *game)
{
	t_door_tex	t;

	t.x_offset = get_door_at(&r, game);
	if (t.x_offset == -1)
		return ;
	if (t.x_offset == 0)
		t.x_offset = game->door.width / 6;
	t.tex = &game->door;
	t.height = t.tex->height;
	t.pitch = t.tex->bpp >> 3;
	t.sc_pitch = screen->bpp >> 3;
	t.sc_line_len = screen->line_len;
	t.len = t.tex->line_len;
	if (r.side == VERTICAL_WALL)
		t.wall_x = game->player.pos.y + r.perp_wall_dist * r.ray_dir_y;
	else
		t.wall_x = game->player.pos.x + r.perp_wall_dist * r.ray_dir_x;
	t.wall_x -= floor(t.wall_x);
	t.tex_x = (int)(t.wall_x * (double)game->door.width / 6);
	t.step = 1.0 * game->door.height / r.line_height;
	t.tex_pos = (r.draw_start - SCREEN_HEIGHT / 2 + r.line_height / 2) * t.step;
	draw_door(screen, r, t, col);
}

static int	verify_hit_wall(t_raycast *r, t_game *game)
{
	while (r->hit == 0)
	{
		if (r->side_dist_x < r->side_dist_y)
		{
			r->side_dist_x += r->delta_dist_x;
			r->map_x += r->step_x;
			r->side = VERTICAL_WALL;
		}
		else
		{
			r->side_dist_y += r->delta_dist_y;
			r->map_y += r->step_y;
			r->side = HORIZONTAL_WALL;
		}
		if (r->map_x < 0 || r->map_y < 0 || r->map_x >= game->map_w
			|| r->map_y >= game->map_h)
		{
			r->hit = 1;
			break;
		}
		if (game->map[r->map_y * game->map_w + r->map_x] == '1')
			return (1);
		else if (game->map[r->map_y * game->map_w + r->map_x] == 'D')
			r->hit = 1;
	}
	return (0);
}

static void	set_direction(t_raycast *r, t_game *game)
{
	r->ray_dir_x = game->player.dir.x + game->player.plane.x * r->camera_x;
	r->ray_dir_y = game->player.dir.y + game->player.plane.y * r->camera_x;
	r->delta_dist_x = fabs(1 / r->ray_dir_x);
	r->delta_dist_y = fabs(1 / r->ray_dir_y);
	if (r->ray_dir_x < 0)
	{
		r->step_x = -1;
		r->side_dist_x = (game->player.pos.x - r->map_x) * r->delta_dist_x;
	}
	else
	{
		r->step_x = 1;
		r->side_dist_x = (r->map_x + 1.0 - game->player.pos.x) * r->delta_dist_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (game->player.pos.y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - game->player.pos.y) * r->delta_dist_y;
	}
}

static void	draw_in_image(t_raycast r, t_image *screen, int col, t_game *game)
{
	r.draw_start = -r.line_height / 2 + SCREEN_HEIGHT / 2;
	if (r.draw_start < 0)
		r.draw_start = 0;
	r.draw_end = r.line_height / 2 + SCREEN_HEIGHT / 2;
	if (r.draw_end >= SCREEN_HEIGHT)
		r.draw_end = SCREEN_HEIGHT - 1;
	draw_column(screen, r, col, game);
}

int	cast_door_rays(t_raycast *r, t_game *game, int column)
{
	r->f_color = game->data->f_color;
	r->c_color = game->data->c_color;
	r->map_x = (int)game->player.pos.x;
	r->map_y = (int)game->player.pos.y;
	r->camera_x = 2.0 * column / (double)SCREEN_WIDTH - 1;
	r->hit = 0;
	r->side = 0;
	set_direction(r, game);
	if (verify_hit_wall(r, game))
		return (1);
	if (r->side == 0)
		r->perp_wall_dist = r->side_dist_x - r->delta_dist_x;
	else
		r->perp_wall_dist = r->side_dist_y - r->delta_dist_y;
	r->line_height = (int)(SCREEN_HEIGHT / r->perp_wall_dist);
	draw_in_image(*r, &game->screen, column, game);
	return (0);
}
