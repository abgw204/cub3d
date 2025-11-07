/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_images.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:19 by gada-sil          #+#    #+#             */
/*   Updated: 2025/11/06 18:06:14 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	images_error(t_game *game)
{
	if (game->settings[0].img)
		mlx_destroy_image(game->mlx, game->settings[0].img);
	if (game->settings[1].img)
		mlx_destroy_image(game->mlx, game->settings[1].img);
	if (game->settings[2].img)
		mlx_destroy_image(game->mlx, game->settings[2].img);
	game->settings[0].img = NULL;
	game->settings[1].img = NULL;
	game->settings[2].img = NULL;
	return (print_error("One or more images failed to load!"));
}

int	load_settings_images(t_game *game)
{
	game->settings[0].img = mlx_xpm_file_to_image(game->mlx,
												  "res/textures/settings/back.xpm",
												  &game->settings[0].width,
												  &game->settings[0].height);
	game->settings[1].img = mlx_xpm_file_to_image(game->mlx,
												  "res/textures/settings/show_fps.xpm",
												  &game->settings[1].width,
												  &game->settings[1].height);
	game->settings[2].img = mlx_xpm_file_to_image(game->mlx,
												  "res/textures/settings/check_box.xpm",
												  &game->settings[2].width,
												  &game->settings[2].height);
	if (!game->settings[0].img || !game->settings[1].img
		|| !game->settings[2].img)
		return (images_error(game));
	return (0);
}
