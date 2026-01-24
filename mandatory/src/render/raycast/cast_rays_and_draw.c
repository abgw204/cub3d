/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays_and_draw.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:54:32 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/24 16:37:24 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static void	draw_column(t_image *screen, t_raycast r, int col, t_game *game)
{
	t_texture	t;

	if (r.side == VERTICAL_WALL)
		t.wall_x = game->player.pos.y + r.perp_wall_dist * r.ray_dir_y;
	else
		t.wall_x = game->player.pos.x + r.perp_wall_dist * r.ray_dir_x;
	t.tex = get_tex(r.ray_dir_x, r.ray_dir_y, r.side, game);
	if (!t.tex)
		return ;
	t.height = t.tex->height;
	t.pitch = t.tex->bpp >> 3;
	t.sc_pitch = screen->bpp >> 3;
	t.sc_line_len = screen->line_len;
	t.len = t.tex->line_len;
	t.wall_x -= floor(t.wall_x);
	t.tex_x = (int)(t.wall_x * (double)t.tex->width);
	t.step = 1.0 * t.tex->height / r.line_height;
	t.tex_pos = (r.draw_start - SCREEN_HEIGHT / 2 + r.line_height / 2) * t.step;
	draw_tex(screen, r, t, col);
}

static void	verify_hit_wall(t_raycast *r, t_game *game)
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
		if (r->map_x < 0 || r->map_y < 0
			|| r->map_x >= game->map_w || r->map_y >= game->map_h)
		{
			r->hit = 1;
			break ;
		}
		if (game->map[r->map_y * game->map_w + r->map_x] == '1')
			r->hit = 1;
	}
}

static void	set_direction(t_raycast *r, t_game *game)
{
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
		r->side_dist_x = (r->map_x + 1.0 - game->player.pos.x)
			* r->delta_dist_x;
	}
	if (r->ray_dir_y < 0)
	{
		r->step_y = -1;
		r->side_dist_y = (game->player.pos.y - r->map_y) * r->delta_dist_y;
	}
	else
	{
		r->step_y = 1;
		r->side_dist_y = (r->map_y + 1.0 - game->player.pos.y)
			* r->delta_dist_y;
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
	draw_ceiling(&r, screen, col, r.draw_start);
	draw_column(screen, r, col, game);
	draw_floor(&r, screen, col, SCREEN_HEIGHT);
}

void	cast_rays_and_draw(t_raycast *r, t_game *game, int column)
{
	r->f_color = game->data->f_color;
	r->c_color = game->data->c_color;
	r->map_x = (int)game->player.pos.x;
	r->map_y = (int)game->player.pos.y;
	r->camera_x = 2.0 * column / (double)SCREEN_WIDTH - 1;
	r->hit = 0;
	r->side = 0;
	r->ray_dir_x = game->player.dir.x + game->player.plane.x * r->camera_x;
	r->ray_dir_y = game->player.dir.y + game->player.plane.y * r->camera_x;
	set_direction(r, game);
	verify_hit_wall(r, game);
	if (r->side == 0)
		r->perp_wall_dist = r->side_dist_x - r->delta_dist_x;
	else
		r->perp_wall_dist = r->side_dist_y - r->delta_dist_y;
	r->line_height = (int)(SCREEN_HEIGHT / r->perp_wall_dist);
	draw_in_image(*r, &game->screen, column, game);
}
