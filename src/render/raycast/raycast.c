/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:39:15 by gada-sil          #+#    #+#             */
/*   Updated: 2025/11/05 04:15:51 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static void    draw_vertical_line(t_image *screen, t_raycast *raycast, int color)
{
    while (raycast->draw_start <= raycast->draw_end)
    {
        draw_pixel_in_image(screen, raycast->collum, raycast->draw_start, color);
        raycast->draw_start++;
    }
}

void	verify_hit_wall(t_raycast *raycast, t_game *game)
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

void	set_direction(t_raycast *raycast, t_game *game)
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

void	draw_in_image(t_raycast *raycast, t_image *screen)
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
		draw_pixel_in_image(screen, raycast->collum, i++, 0x9999FF);
	draw_vertical_line(screen, raycast, 0x000000);
	i = raycast->draw_end;
	while (i < SCREEN_HEIGHT)
		draw_pixel_in_image(screen, raycast->collum, i++, 0x888888);
}

void    raycast(t_game *game)
{
	t_raycast	raycast;

	raycast.collum = 0;
    while (raycast.collum < SCREEN_WIDTH)
    {
		raycast.map_x = (int)game->player.pos.x;
        raycast.map_y = (int)game->player.pos.y;
        raycast.camera_x = 2.0 * raycast.collum / (double)SCREEN_WIDTH - 1;
		set_direction(&raycast, game);
		verify_hit_wall(&raycast, game);
        if (raycast.side == 0)
            raycast.perp_wall_dist = raycast.side_dist_x - raycast.delta_dist_x;
        else
            raycast.perp_wall_dist = raycast.side_dist_y - raycast.delta_dist_y;
        raycast.perp_wall_dist_corrected = raycast.perp_wall_dist * 
        (game->player.dir.x * raycast.ray_dir_x + game->player.dir.y * raycast.ray_dir_y);
        raycast.line_height = (int)(SCREEN_HEIGHT / raycast.perp_wall_dist_corrected);
        draw_in_image(&raycast, &game->screen);
        raycast.collum++;
    }
}
