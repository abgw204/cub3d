/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 04:19:39 by gada-sil          #+#    #+#             */
/*   Updated: 2025/12/04 12:02:11 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int key_release(int key, void *param)
{
    t_game *game;

    game = (t_game *)param;
    if (key == KEY_W)
        game->keys[0] = '0';
    else if (key == KEY_A)
        game->keys[1] = '0';
    else if (key == KEY_S)
        game->keys[2] = '0';
    else if (key == KEY_D)
        game->keys[3] = '0';
    else if (key == LEFT_ARROW)
        game->keys[4] = '0';
    else if (key == RIGHT_ARROW)
        game->keys[5] = '0';
    else if (key == KEY_ESC)
    {
        game->state = MAIN_MENU; // teste
    }
    return (0);
}

int key_press(int key, void *param)
{
    t_game *game;

    game = (t_game *)param;
    if (key == KEY_W)
        game->keys[0] = '1';
    else if (key == KEY_A)
        game->keys[1] = '1';
    else if (key == KEY_S)
        game->keys[2] = '1';
    else if (key == KEY_D)
        game->keys[3] = '1';
    else if (key == LEFT_ARROW)
        game->keys[4] = '1';
    else if (key == RIGHT_ARROW)
		game->keys[5] = '1';
    return (0);
}
