/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:34 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/24 17:05:35 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int	render_main_menu(t_game *game)
{
	(void)game;
	// eventualmente trocar game->state de MAIN_MENU para IN_GAME
	return (0);
}

int	main_menu_inputs(int mouse_btn, int x, int y, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	printf("%d\n", mouse_btn);
	(void)game;
	(void)x;
	(void)y;
	return (0);
}
