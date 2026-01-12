/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 11:12:04 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/12 11:35:15 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int	close_window_x(void *param)
{
	t_game		*game;

	game = (t_game *)param;
	free_and_exit(game);
	return (0);
}

int	load_mlx_window(t_game *game)
{
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	if (!game->win)
		return (print_error_free(game, "Mlx window did not work correctly!"));
	return (0);
}
