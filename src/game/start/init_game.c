/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:19 by gada-sil          #+#    #+#             */
/*   Updated: 2025/11/04 20:40:40 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static int	update(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_clear_window(game->mlx, game->win);
	set_delta_time(game);
	limit_fps(60.0);
	if (game->state == MAIN_MENU)
		show_main_menu(game);
	else if (game->state == IN_GAME)
		game_loop(game);
	else if (game->state == IN_SETTINGS)
		show_settings(game);
	free(game->fps);
    game->fps = NULL;
	return (0);
}

int	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (print_error_free(game, "Mlx context did not work correctly!"));
	if (configure_menu_images(game))
		return (print_error_free(game, NULL));
	if (configure_settings_images(game))
		return (print_error_free(game, NULL));
	if (configure_screen_image(game))
		return (print_error_free(game, NULL));
	game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d");
	if (!game->win)
		return (print_error_free(game, "Mlx window did not work correctly!"));
	load_minimap(game);
	mlx_loop_hook(game->mlx, update, game);
	mlx_mouse_hook(game->win, mouse_input, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_move, game);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_loop(game->mlx);
	return (0);
}
