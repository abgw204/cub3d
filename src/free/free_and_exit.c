/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:19 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/24 17:05:20 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	free_images(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
		mlx_destroy_image(game->mlx, game->menu_btns[i++].img);
	i = 0;
	while (i < 3)
		mlx_destroy_image(game->mlx, game->settings[i++].img);
}

void	free_and_exit(t_game *game)
{
	int	i;

	i = 0;
	while (i < 6)
		free_matrix(game->data->config[i++]);
	free_images(game);
	free(game->keys);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
}
