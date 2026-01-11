/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:19 by gada-sil          #+#    #+#             */
/*   Updated: 2025/12/12 12:54:48 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	set_buttons_pos_sett(t_image *settings)
{
	settings[0].x = SCREEN_WIDTH / 2 - 350;
	settings[0].y = 95;
	settings[1].x = SCREEN_WIDTH / 2 - 180;
	settings[1].y = 300;
	settings[2].x = SCREEN_WIDTH / 2 + 130;
	settings[2].y = 297;
}

int	configure_settings_images(t_game *game)
{
	if (load_settings_images(game))
		return (1);
	set_buttons_pos_sett(game->settings);
	set_settings_images_info(game->settings);
	set_menu_images_info(game->menu_btns);
	return (0);
}

int	show_settings(t_game *game)
{
	int	i;

	i = -1;
	mouse_move_settings(game, game->m_x, game->m_y);
	mlx_put_image_to_window(game->mlx, game->win,
		game->menu_btns[2].img,
		game->menu_btns[2].x,
		game->menu_btns[2].y - 450);
	while (++i < 3)
		mlx_put_image_to_window(game->mlx, game->win,
			game->settings[i].img,
			game->settings[i].x,
			game->settings[i].y);
	return (0);
}
