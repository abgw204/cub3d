/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:19 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/02 15:15:39 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_textures(t_game *game)
{
	if (game->n.img)
		mlx_destroy_image(game->mlx, game->n.img);
	if (game->s.img)
		mlx_destroy_image(game->mlx, game->s.img);
	if (game->w.img)
		mlx_destroy_image(game->mlx, game->w.img);
	if (game->e.img)
		mlx_destroy_image(game->mlx, game->e.img);
	if (game->gun.img)
		mlx_destroy_image(game->mlx, game->gun.img);
	if (game->door.img)
		mlx_destroy_image(game->mlx, game->door.img);
}

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
	if (game->minimap.img.img)
		mlx_destroy_image(game->mlx, game->minimap.img.img);
	if (game->screen.img)
		mlx_destroy_image(game->mlx, game->screen.img);
}

void	free_and_exit(t_game *game)
{
	int	i;

	i = 0;
	game->stop = true;
	start_all_render_threads(&game->cond_start, &game->m);
	wait_all_render_threads(&game->cond_done, &game->m);
	while (i < 6)
		free_matrix(game->data->config[i++]);
	free_images(game);
	free_textures(game);
	free(game->doors);
	free(game->keys);
	free(game->map);
	free(game->fps);
	ft_lstclear(&game->data->map_list, free);
	if (game->mlx)
	{
		mlx_destroy_window(game->mlx, game->win);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(0);
}
