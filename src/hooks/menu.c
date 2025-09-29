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

#include "../../include/cub3d.h"

static int	get_button_pos(const char *imgs)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (imgs[i] == '1')
			return (i);
		i++;
	}
	return (-1);
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
		revert_colors(&game->menu_btns[i], 0x000000, 0xFFFFFE);
		imgs[i] = '1';
		return (0);
	}
	else if (i == 4 && get_button_pos(imgs) != -1)
	{
		if (!check_btn_collision(&game->menu_btns[get_button_pos(imgs)], x, y))
		{
			revert_colors(&game->menu_btns[get_button_pos(imgs)], 0xFFFFFE, 0x000000);
			imgs[get_button_pos(imgs)] = '0';
		}
	}
	return (0);
}
