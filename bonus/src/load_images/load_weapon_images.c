/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_weapon_images.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:48:46 by gada-sil          #+#    #+#             */
/*   Updated: 2025/12/12 13:40:29 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	load_weapon_images(t_game *game)
{
	game->gun.img = mlx_xpm_file_to_image(game->mlx,
								"bonus/res/textures/sprites/gun/gun_spritesheet.xpm",
								&game->gun.width,
								&game->gun.height);
	if (!game->gun.img)
		return (print_error("One or more images failed to load!"));
	game->gun.addr = mlx_get_data_addr(game->gun.img,
		&game->gun.bpp, &game->gun.line_len, &game->gun.endian);
	return (0);
}