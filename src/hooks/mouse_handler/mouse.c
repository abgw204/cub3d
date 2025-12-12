/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:19 by gada-sil          #+#    #+#             */
/*   Updated: 2025/12/12 12:23:30 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int	mouse_move_in_game(t_game *game, int x)
{
	int	middle;

	middle = SCREEN_WIDTH / 2;
	rotate_camera_mouse(game, middle, x);
	mlx_mouse_move(game->mlx, game->win, middle, SCREEN_HEIGHT / 2);
	return (0);
}

int	mouse_move(int x, int y, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game->m_x = x;
	game->m_y = y;
	return (0);
}

int	mouse_input(int mouse_btn, int x, int y, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (game->state == IN_GAME)
		/*return (mouse_input_in_game(game, x, y))*/{}
	if (game->state == MAIN_MENU)
		return (mouse_input_menu(game, x, y, mouse_btn));
	if (game->state == IN_SETTINGS)
		return (mouse_input_in_settings(game, x, y, mouse_btn));
	//system("paplay ../../screenshot-iphone-sound-336170.wav &");
	return (0);
}
