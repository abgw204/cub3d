/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays_and_draw.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:54:32 by gada-sil          #+#    #+#             */
/*   Updated: 2025/11/07 08:29:15 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static void    draw_vertical_line(t_image *screen, t_raycast *raycast, int color, int start)
{
    while (raycast->draw_start <= raycast->draw_end)
    {
		if (raycast->side == 1)
			draw_pixel_in_image(screen, start, raycast->draw_start, color);
		else
			draw_pixel_in_image(screen, start, raycast->draw_start, 0x6666FF);
        raycast->draw_start++;
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
			break; // evita sair dos limites
		}
		// verifica se chegou em uma parede
		if (game->map[raycast->map_y * game->map_w + raycast->map_x] == '1')
			raycast->hit = 1;
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

static void	draw_in_image(t_raycast *raycast, t_image *screen, int start)
{
	int	i;
	
	i = 0;
	raycast->draw_start = -raycast->line_height / 2 + SCREEN_HEIGHT / 2;
	if (raycast->draw_start < 0)
		raycast->draw_start = 0;
	raycast->draw_end = raycast->line_height / 2 + SCREEN_HEIGHT / 2;
	if (raycast->draw_end >= SCREEN_HEIGHT)
		raycast->draw_end = SCREEN_HEIGHT - 1;
	while (i < raycast->draw_start)
	{
		if (i >= raycast->draw_start - 3)
		{
			draw_pixel_in_image(screen, start, i++, 0x0000FF);
			continue ;
		}
		draw_pixel_in_image(screen, start, i++, 0x9999FF);
	}
	draw_vertical_line(screen, raycast, 0x111184, start);
	i = raycast->draw_end;
	while (i < SCREEN_HEIGHT)
	{
		if (i <= raycast->draw_end + 3)
		{
			draw_pixel_in_image(screen, start, i++, 0x0000FF);
			continue ;
		}
		draw_pixel_in_image(screen, start, i, 0x888888);
		i++;
	}
}

void	cast_rays_and_draw(t_raycast *r, t_game *game, int *start)
{
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
	draw_in_image(r, &game->screen, *start);
	game->z_buffer[*start] = r->perp_wall_dist;
	(*start)++;
}
