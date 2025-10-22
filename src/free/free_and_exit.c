/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:19 by gada-sil          #+#    #+#             */
/*   Updated: 2025/10/14 20:03:40 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_images(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->menu_btns[i].img)
			mlx_destroy_image(game->mlx, game->menu_btns[i].img);
		i++;
	}
	i = 0;
	while (i < 3)
	{
		if (game->settings[i].img)
			mlx_destroy_image(game->mlx, game->settings[i].img);
		i++;
	}
	if (game->minimap.minimap_img.img)
		mlx_destroy_image(game->mlx, game->minimap.minimap_img.img);
}

void	free_and_exit(t_game *game)
{
	int	i;

	i = 0;
	while (i < 6)
		free_matrix(game->data->config[i++]);
	free_images(game);
	free(game->keys);
	free(game->map);
	ft_lstclear(&game->data->map_list, free);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
}
