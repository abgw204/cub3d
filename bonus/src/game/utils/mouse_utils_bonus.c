/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:07:19 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/24 15:35:39 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

void	disable_mouse(t_game *game)
{
	if (game->config.show_mouse == false)
		return ;
	mlx_mouse_hide(game->mlx, game->win);
	game->config.show_mouse = false;
}

void	enable_mouse(t_game *game)
{
	if (game->config.show_mouse == true)
		return ;
	mlx_mouse_show(game->mlx, game->win);
	game->config.show_mouse = true;
}
