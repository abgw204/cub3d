/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:19 by gada-sil          #+#    #+#             */
/*   Updated: 2025/10/17 18:03:47 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	get_button_pos(const char *imgs, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (imgs[i] == '1')
			return (i);
		i++;
	}
	return (-1);
}

int	mouse_input_menu(t_game *game, int x, int y, int mouse_btn)
{
	if (mouse_btn == 1)
	{
		game->player.pos.y -= game->player.speed * g_delta_time;
	}
	if (mouse_btn == 5)
	{
		game->player.pos.x -= game->player.speed * g_delta_time;
	}
	if (mouse_btn == 4)
	{
		game->player.pos.x += game->player.speed * g_delta_time;
	}
	if (mouse_btn == 3)
	{
		game->player.pos.y += game->player.speed * g_delta_time;
	}
	if (check_btn_collision(&game->menu_btns[2], x, y) && mouse_btn == 1)
	{
		revert_colors(&game->menu_btns[2], WHITE_ISH, BLACK);
		game->state = IN_SETTINGS;
	}
	else if (check_btn_collision(&game->menu_btns[3], x, y) && mouse_btn == 1)
		free_and_exit(game);
	return (0);
}

int	mouse_input_in_settings(t_game *game, int x, int y, int mouse_btn)
{
	if (check_btn_collision(&game->settings[0], x, y) && mouse_btn == 1)
	{
		revert_colors(&game->settings[0], WHITE_ISH, BLACK);
		game->state = MAIN_MENU;
	}
	else if (check_btn_collision(&game->settings[2], x, y) && mouse_btn == 1)
	{
		if (game->config.show_fps == 0)
		{
			game->config.show_fps = 1;
			revert_colors(&game->settings[2], BLACK, WHITE_ISH);
		}
		else
		{
			game->config.show_fps = 0;
			revert_colors(&game->settings[2], WHITE_ISH, BLACK);
		}
	}
	return (0);
}

int	mouse_move_settings(t_game *game, int x, int y)
{
	static char	imgs[4] = "000";
	int			i;

	i = 0;
	while (i < 2)
	{
		if (check_btn_collision(&game->settings[i], x, y))
			break ;
		i++;
	}
	if (i != 2 && imgs[i] == '0')
	{
		revert_colors(&game->settings[i], BLACK, WHITE_ISH);
		imgs[i] = '1';
		return (0);
	}
	else if (i == 2 && get_button_pos(imgs, 2) != -1)
	{
		if (!check_btn_collision(&game->settings[get_button_pos(imgs, 2)], x, y))
		{
			revert_colors(&game->settings[get_button_pos(imgs, 2)], WHITE_ISH, BLACK);
			imgs[get_button_pos(imgs, 2)] = '0';
		}
	}
	return (0);
}

int	mouse_move_menu(t_game *game, int x, int y)
{
	static char	imgs[5] = "0000";
	int			i;

	i = 1;
	while (i < 4)
	{
		if (check_btn_collision(&game->menu_btns[i], x, y))
			break ;
		i++;
	}
	if (i != 4 && imgs[i] == '0')
	{
		revert_colors(&game->menu_btns[i], BLACK, WHITE_ISH);
		imgs[i] = '1';
		return (0);
	}
	else if (i == 4 && get_button_pos(imgs, 4) != -1)
	{
		if (!check_btn_collision(&game->menu_btns[get_button_pos(imgs, 4)], x, y))
		{
			revert_colors(&game->menu_btns[get_button_pos(imgs, 4)], WHITE_ISH, BLACK);
			imgs[get_button_pos(imgs, 4)] = '0';
		}
	}
	return (0);
}
