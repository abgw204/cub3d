/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu_images.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:19 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/24 17:05:20 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	load_menu_images(t_game *game)
{
	game->menu_images[0].img = mlx_xpm_file_to_image(game->mlx,
												  "res/textures/cub3d.xpm",
												  &game->menu_images[0].width,
												  &game->menu_images[0].height);
	if (!game->menu_images[0].img)
		return (1);
	game->menu_images[1].img = mlx_xpm_file_to_image(game->mlx,
												  "res/textures/start.xpm",
												  &game->menu_images[1].width,
												  &game->menu_images[1].height);
	if (!game->menu_images[1].img)
	{
		mlx_destroy_image(game->mlx, game->menu_images[0].img);
		return (1);
	}
	game->menu_images[2].img = mlx_xpm_file_to_image(game->mlx,
												  "res/textures/settings.xpm",
												  &game->menu_images[2].width,
												  &game->menu_images[2].height);
	if (!game->menu_images[2].img)
	{
		mlx_destroy_image(game->mlx, game->menu_images[0].img);
		mlx_destroy_image(game->mlx, game->menu_images[1].img);
		return (1);
	}
	return (0);
}
