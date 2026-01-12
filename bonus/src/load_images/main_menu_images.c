/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu_images.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:19 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/12 11:51:13 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	images_error(t_game *game)
{
	if (game->menu_btns[0].img)
		mlx_destroy_image(game->mlx, game->menu_btns[0].img);
	if (game->menu_btns[1].img)
		mlx_destroy_image(game->mlx, game->menu_btns[1].img);
	if (game->menu_btns[2].img)
		mlx_destroy_image(game->mlx, game->menu_btns[2].img);
	if (game->menu_btns[3].img)
		mlx_destroy_image(game->mlx, game->menu_btns[3].img);
	game->menu_btns[0].img = NULL;
	game->menu_btns[1].img = NULL;
	game->menu_btns[2].img = NULL;
	game->menu_btns[3].img = NULL;
	return (print_error("One or more images failed to load!3"));
}

int	load_menu_images(t_game *game)
{
	game->menu_btns[0].img = mlx_xpm_file_to_image(game->mlx,
			"bonus/res/textures/menu/cub3d.xpm",
			&game->menu_btns[0].width,
			&game->menu_btns[0].height);
	game->menu_btns[1].img = mlx_xpm_file_to_image(game->mlx,
			"bonus/res/textures/menu/start.xpm",
			&game->menu_btns[1].width,
			&game->menu_btns[1].height);
	game->menu_btns[2].img = mlx_xpm_file_to_image(game->mlx,
			"bonus/res/textures/menu/settings.xpm",
			&game->menu_btns[2].width,
			&game->menu_btns[2].height);
	game->menu_btns[3].img = mlx_xpm_file_to_image(game->mlx,
			"bonus/res/textures/menu/exit.xpm",
			&game->menu_btns[3].width,
			&game->menu_btns[3].height);
	if (!game->menu_btns[0].img || !game->menu_btns[1].img
		|| !game->menu_btns[2].img || !game->menu_btns[3].img)
		return (images_error(game));
	return (0);
}
