/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:12:04 by gada-sil          #+#    #+#             */
/*   Updated: 2025/12/08 11:24:59 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int	load_enemy_sprite(t_game *game)
{
	game->enemy.img = mlx_xpm_file_to_image(game->mlx,
		"res/textures/sprites/enemy.xpm", &game->enemy.width,
		&game->enemy.height);
	if (!game->enemy.img)
		return (print_error("Enemy image failed to load!"));
	game->enemy.addr = mlx_get_data_addr(game->enemy.img,
		&game->enemy.bpp, &game->enemy.line_len, &game->enemy.endian);
	return (0);
}

int	load_mlx_window(t_game *game)
{
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	if (!game->win)
		return (print_error_free(game, "Mlx window did not work correctly!"));
	return (0);
}