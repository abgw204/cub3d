/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:19 by gada-sil          #+#    #+#             */
/*   Updated: 2025/11/07 08:15:55 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	set_game_hooks(t_game *game)
{
	mlx_loop_hook(game->mlx, (int (*)())update, game);
	mlx_mouse_hook(game->win, (int (*)())mouse_input, game);
	mlx_hook(game->win, 6, 1L << 6, (int (*)())mouse_move, game);
	mlx_hook(game->win, 2, 1L << 0, (int (*)())key_press, game);
	mlx_hook(game->win, 3, 1L << 1, (int (*)())key_release, game);
}

static int	load_game_textures(t_game *game)
{
	if (configure_menu_images(game))
		return (print_error_free(game, NULL));
	if (configure_settings_images(game))
		return (print_error_free(game, NULL));
	if (configure_screen_image(game))
		return (print_error_free(game, NULL));
	//if (configure_textures_images(game))
	//	return (print_error_free(game, NULL));
	return (0);
}

static int	load_mlx_context(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (print_error_free(game, "Mlx context did not work correctly!"));
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	if (!game->win)
		return (print_error_free(game, "Mlx window did not work correctly!"));
	return (0);
}

void	init_threads(t_game *game)
{
	int	i;

	i = 0;
	game->id = i;
	game->threads_done = i;
	pthread_cond_init(&game->cond_done, NULL);
	pthread_cond_init(&game->cond_start, NULL);
	pthread_mutex_init(&game->m, NULL);
	while (i < N_THREADS)
		thread_create(&game->th[i++], &raycast, game);
}

int	init_game(t_game *game)
{
	if (load_mlx_context(game))
		return (1);
	if (load_game_textures(game))
		return (1);
	if (load_minimap(game))
		return (1);
	game->z_buffer = (double *)malloc(SCREEN_WIDTH * sizeof(double));
	set_game_hooks(game);
	init_threads(game);
	mlx_loop(game->mlx);
	return (0);
}
