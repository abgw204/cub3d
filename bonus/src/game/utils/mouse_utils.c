/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:07:19 by gada-sil          #+#    #+#             */
/*   Updated: 2025/11/06 16:14:39 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void    disable_mouse(t_game *game)
{
    if (game->config.show_mouse == false)
        return ;
    mlx_mouse_hide(game->mlx, game->win);
    game->config.show_mouse = false;
}

void    enable_mouse(t_game *game)
{
    if (game->config.show_mouse == true)
        return ;
    mlx_mouse_show(game->mlx, game->win);
    game->config.show_mouse = true;
}