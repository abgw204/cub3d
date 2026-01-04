/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays_and_draw.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:54:32 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/02 19:44:44 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static void    draw_vertical_line(t_image *screen, t_raycast *raycast, int start, t_game *game)
{
	t_raycast	r;
	char		*dst;
	int			pitch;
	int			line_len;
	double		wall_x;

	t_image *tex = NULL;
	r = *raycast;
	pitch = screen->bpp >> 3;
	line_len = screen->line_len;
	if (r.side == 0)
	{
		wall_x = game->player.pos.y + r.perp_wall_dist * r.ray_dir_y;
		if (r.ray_dir_x > 0.0)
			tex = &game->e;
		else
			tex = &game->w;
	}
	else
	{
		wall_x = game->player.pos.x + r.perp_wall_dist * r.ray_dir_x;
		if (r.ray_dir_y > 0.0)
			tex = &game->s;
		else
			tex = &game->n;
	}
	wall_x -= floor(wall_x);
	int tex_x = (int)(wall_x * (double)game->n.width);
	double step = 1.0 * game->n.height / r.line_height;
	double texPos = (r.draw_start - SCREEN_HEIGHT / 2 + r.line_height / 2) * step;
    while (r.draw_start <= r.draw_end)
    {
	    int texY = (int)texPos % game->n.height;
	    texPos += step;
	    unsigned int color = *(unsigned int *)
			(
				tex->addr
				+ (texY * tex->line_len)
				+ (tex_x * pitch)
			);
		dst = screen->addr
			+ r.draw_start * line_len
			+ start * pitch;
		*(unsigned int *)dst = color;
        r.draw_start++;
    }
}

static void	verify_hit_wall(t_raycast *raycast, t_game *game)
{
	raycast->hit = 0;
	raycast->side = 0;
	while (raycast->hit == 0)
	{
		if (raycast->side_dist_x < raycast->side_dist_y)
		{
			raycast->side_dist_x += raycast->delta_dist_x;
			raycast->map_x += raycast->step_x;
			raycast->side = 0; // bateu numa parede vertical
		}
		else
		{
			raycast->side_dist_y += raycast->delta_dist_y;
			raycast->map_y += raycast->step_y;
			raycast->side = 1; // bateu numa parede horizontal
		}
		if (raycast->map_x < 0 || raycast->map_y < 0 || raycast->map_x >= game->map_w || raycast->map_y >= game->map_h)
		{
			raycast->hit = 1;
			break;
		}
		// verifica se chegou em uma parede
		if (game->map[raycast->map_y * game->map_w + raycast->map_x] == '1')
			raycast->hit = 1;
		else if (game->map[raycast->map_y * game->map_w + raycast->map_x] == 'D')
			raycast->hit = 0;
	}
}

static void	set_direction(t_raycast *raycast, t_game *game)
{
	raycast->ray_dir_x = game->player.dir.x + game->player.plane.x * raycast->camera_x;
	raycast->ray_dir_y = game->player.dir.y + game->player.plane.y * raycast->camera_x;
	raycast->delta_dist_x = fabs(1 / raycast->ray_dir_x);
	raycast->delta_dist_y = fabs(1 / raycast->ray_dir_y);
	if (raycast->ray_dir_x < 0)
	{
		raycast->step_x = -1;
		raycast->side_dist_x = (game->player.pos.x - raycast->map_x) * raycast->delta_dist_x;
	}
	else
	{
		raycast->step_x = 1;
		raycast->side_dist_x = (raycast->map_x + 1.0 - game->player.pos.x) * raycast->delta_dist_x;
	}
	if (raycast->ray_dir_y < 0)
	{
		raycast->step_y = -1;
		raycast->side_dist_y = (game->player.pos.y - raycast->map_y) * raycast->delta_dist_y;
	}
	else
	{
		raycast->step_y = 1;
		raycast->side_dist_y = (raycast->map_y + 1.0 - game->player.pos.y) * raycast->delta_dist_y;
	}
}

static void	draw_in_image(t_raycast r, t_image *screen, int start, t_game *game)
{
	r.draw_start = -r.line_height / 2 + SCREEN_HEIGHT / 2;
	if (r.draw_start < 0)
		r.draw_start = 0;
	r.draw_end = r.line_height / 2 + SCREEN_HEIGHT / 2;
	if (r.draw_end >= SCREEN_HEIGHT)
		r.draw_end = SCREEN_HEIGHT - 1;
	draw_ceiling(&r, screen, start, r.draw_start);
	draw_vertical_line(screen, &r, start, game);
	draw_floor(&r, screen, start, SCREEN_HEIGHT);
}

void	cast_rays_and_draw(t_raycast *r, t_game *game, int *start)
{
	r->f_color = game->data->f_color;
	r->c_color = game->data->c_color;
	r->map_x = (int)game->player.pos.x;
	r->map_y = (int)game->player.pos.y;
	r->camera_x = 2.0 * (*start) / (double)SCREEN_WIDTH - 1;
	set_direction(r, game);
	verify_hit_wall(r, game);
	if (r->side == 0)
		r->perp_wall_dist = r->side_dist_x - r->delta_dist_x;
	else
		r->perp_wall_dist = r->side_dist_y - r->delta_dist_y;
	r->line_height = (int)(SCREEN_HEIGHT / r->perp_wall_dist);
	draw_in_image(*r, &game->screen, *start, game);
	(*start)++;
}
