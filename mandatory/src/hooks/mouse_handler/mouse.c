/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:19 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/24 16:35:55 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int	mouse_move(int x, int y, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	game->m_x = x;
	game->m_y = y;
	return (0);
}

static int	mouse_input_in_game(t_game *game, int mouse_btn)
{
	if (mouse_btn == 1 && game->is_shooting == false
		&& game->shoot_timer >= SHOOT_DELAY)
	{
		game->keys[6] = '1';
		game->shoot_timer = 0.0;
	}
	return (0);
}

int	mouse_input(int mouse_btn, int x, int y, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (game->state == IN_GAME)
		return (mouse_input_in_game(game, mouse_btn));
	if (game->state == MAIN_MENU)
		return (mouse_input_menu(game, x, y, mouse_btn));
	if (game->state == IN_SETTINGS)
		return (mouse_input_in_settings(game, x, y, mouse_btn));
	return (0);
}
