/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:19 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/24 17:05:20 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static int	update(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_clear_window(game->mlx, game->win);
	set_delta_time(game);
	limit_fps(120.0);
	if (game->state == MAIN_MENU)
		return (show_main_menu(game));
	if (game->state == IN_GAME)
		/*return (game_loop(game))*/{}
	if (game->state == IN_SETTINGS)
		return (show_settings(game));
	return (0);
}

int	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (print_error_free(game, "Mlx context did not work correctly!"));
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	if (!game->win)
		return (print_error_free(game, "Mlx window did not work correctly!"));
	if (load_menu_images(game))
		return (print_error_free(game, "Missing game files!"));
	set_buttons_pos(game->menu_images);
	game->menu_images[1].addr = mlx_get_data_addr(game->menu_images[1].img,
		&game->menu_images[1].bpp,
		&game->menu_images[1].line_len,
		&game->menu_images[1].endian);
	mlx_loop_hook(game->mlx, (int (*)())update, game);
	mlx_hook(game->win, 5, 1L<<3, (int (*)())mouse_input, game);
	mlx_hook(game->win, 6, 1L<<6, (int (*)())mouse_move, game);
	mlx_loop(game->mlx);
	return (0);
}
