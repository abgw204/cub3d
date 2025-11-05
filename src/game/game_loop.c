/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:54:32 by gada-sil          #+#    #+#             */
/*   Updated: 2025/11/04 21:15:55 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void    clear_screen_image(t_game *game)
{
    int x;
    int y;

    x = -1;
    y = -1;
    while (++y < SCREEN_HEIGHT)
    {
        while (++x < SCREEN_WIDTH)
            draw_pixel_in_image(&game->screen, x, y, 0x000000);
        x = -1;
    }
}

int game_loop(t_game *game)
{
    clear_screen_image(game);
    rotate_camera(game);
    move_player(game);
    raycast(game);
    mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
    if (game->config.show_fps && game->fps)
    {
        mlx_string_put(game->mlx, game->win, SCREEN_WIDTH - (SCREEN_WIDTH - 30),
		SCREEN_HEIGHT - (SCREEN_HEIGHT - 30), 0xFFFFFF, game->fps);
    }
	draw_minimap(game);
    return (0);
}