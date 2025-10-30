/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_screen_image.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:39:01 by gada-sil          #+#    #+#             */
/*   Updated: 2025/10/30 18:53:08 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int configure_screen_image(t_game *game)
{
    int x;
    int y;

    mlx_get_screen_size(game->mlx, &x, &y);
    game->screen.img = mlx_new_image(game->mlx, x, y);
    if (!game->screen.img)
        return (1);
    game->screen.addr = mlx_get_data_addr(game->screen.img,
        &game->screen.bpp, &game->screen.line_len, &game->screen.endian);
    return (0);
}