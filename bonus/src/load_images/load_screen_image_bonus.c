/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_screen_image_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:39:01 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/24 15:37:39 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	configure_screen_image(t_game *game)
{
	game->screen.img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!game->screen.img)
		return (1);
	game->screen.addr = mlx_get_data_addr(game->screen.img,
			&game->screen.bpp, &game->screen.line_len, &game->screen.endian);
	return (0);
}
