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
	set_delta_time();
	mlx_clear_window(game->mlx, game->win);
	if (game->state == MAIN_MENU)
		return (render_main_menu(game));
	if (game->state == IN_GAME)
		/*return (game_loop(game))*/{}
	return (0);
}

int	init_game(t_game *game)
{
	game->mlx = mlx_init();
	if (!game->mlx)
		return (print_error_free(game, "mlx context did not work correctly"));
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3d");
	if (!game->win)
		return (print_error_free(game, "mlx window did not work correctly"));
	game->img.img = mlx_new_image(game->mlx, 140, 140);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.line_len, &game->img.endian);
	t_vector2 pos = {.x = 70, .y = 70};
	draw_circle(pos, 50, 16777215, &game->img);
	mlx_loop_hook(game->mlx, (int (*)())update, game);
	mlx_hook(game->win, 5, 1L<<3, (int (*)())main_menu_inputs, game);
	mlx_loop(game->mlx);
	return (0);
}
