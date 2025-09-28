/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:19 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/24 17:05:20 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int	mouse_move(int x, int y, void *param)
{
	t_game		*game;

	game = (t_game *)param;
	(void)game;
	(void)x;
	(void)y;
	/*if (game->state == IN_GAME)
		return (mouse_move_in_game(game, x, y));
	if (game->state == MAIN_MENU)
		return (mouse_move_menu(game, x, y));
	if (game->state == IN_SETTINGS)
		return (mouse_move_in_settings(game, x, y));*/
	return (0);
}

int	mouse_input(int mouse_btn, int x, int y, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	(void)mouse_btn;
	(void)x;
	(void)y;
	(void)game;
	/*if (game->state == IN_GAME)
		return (mouse_input_in_game(game, x, y, mouse_btn));
	if (game->state == MAIN_MENU)
		return (mouse_input_menu(game, x, y, mouse_btn));
	if (game->state == IN_SETTINGS)
		return (mouse_input_in_settings(game, x, y, mouse_btn));*/
	return (0);
}
