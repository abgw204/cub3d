/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_weapon_images.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 14:48:46 by gada-sil          #+#    #+#             */
/*   Updated: 2025/12/08 15:02:37 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	images_error(t_game *game)
{
	if (game->gun[0].img)
		mlx_destroy_image(game->mlx, game->gun[0].img);
	if (game->gun[1].img)
		mlx_destroy_image(game->mlx, game->gun[1].img);
	if (game->gun[2].img)
		mlx_destroy_image(game->mlx, game->gun[2].img);
	if (game->gun[3].img)
		mlx_destroy_image(game->mlx, game->gun[3].img);
    if (game->gun[4].img)
		mlx_destroy_image(game->mlx, game->gun[4].img);
	game->gun[0].img = NULL;
	game->gun[1].img = NULL;
	game->gun[2].img = NULL;
	game->gun[3].img = NULL;
	game->gun[4].img = NULL;
	return (print_error("One or more images failed to load!"));
}

int	load_weapon_images(t_game *game)
{
	game->gun[0].img = mlx_xpm_file_to_image(game->mlx,
												  "res/textures/sprites/gun/gun0.xpm",
												  &game->gun[0].width,
												  &game->gun[0].height);
	game->gun[1].img = mlx_xpm_file_to_image(game->mlx,
												  "res/textures/sprites/gun/gun1.xpm",
												  &game->gun[1].width,
												  &game->gun[1].height);
	game->gun[2].img = mlx_xpm_file_to_image(game->mlx,
												  "res/textures/sprites/gun/gun2.xpm",
												  &game->gun[2].width,
												  &game->gun[2].height);
	game->gun[3].img = mlx_xpm_file_to_image(game->mlx,
												  "res/textures/sprites/gun/gun3.xpm",
												  &game->gun[3].width,
												  &game->gun[3].height);
    game->gun[4].img = mlx_xpm_file_to_image(game->mlx,
												  "res/textures/sprites/gun/gun4.xpm",
												  &game->gun[4].width,
												  &game->gun[4].height);
	if (!game->gun[0].img || !game->gun[1].img
		|| !game->gun[2].img || !game->gun[3].img
            || !game->gun[4].img)
		return (images_error(game));
	return (0);
}