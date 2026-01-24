/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:19 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/24 16:19:47 by gada-sil         ###   ########.fr       */
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
	mlx_hook(game->win, 17, 0, (int (*)())close_window_x, game);
}

static int	load_game_textures(t_game *game)
{
	if (configure_menu_images(game))
		return (print_error_free(game, NULL));
	if (configure_settings_images(game))
		return (print_error_free(game, NULL));
	if (configure_screen_image(game))
		return (print_error_free(game, NULL));
	if (configure_textures_images(game))
		return (print_error_free(game, NULL));
	if (load_weapon_images(game))
		return (print_error_free(game, NULL));
	return (0);
}

static int	load_mlx_context(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (print_error_free(game, "Mlx context did not work correctly!"));
	return (0);
}

int	init_game(t_game *game)
{
	if (load_mlx_context(game))
		return (1);
	if (load_game_textures(game))
		return (1);
	if (load_mlx_window(game))
		return (1);
	set_game_hooks(game);
	mlx_loop(game->mlx);
	return (0);
}
