/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:54:32 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/24 16:32:54 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	show_fps(t_game *game)
{
	if (game->config.show_fps && game->fps)
	{
		mlx_string_put(game->mlx, game->win, SCREEN_WIDTH - (SCREEN_WIDTH - 30),
			SCREEN_HEIGHT - (SCREEN_HEIGHT - 30), 0xFFFFFF, game->fps);
	}
}

void	draw_crosshair(t_image *screen)
{
	t_iv2	pos;

	pos.x = SCREEN_WIDTH / 2 - 2;
	pos.y = SCREEN_HEIGHT / 2 - 2;
	draw_square(pos, 2, WHITE, screen);
}

int	game_loop(t_game *game)
{
	move_player(game);
	raycast(game);
	draw_sprites(game);
	draw_crosshair(&game->screen);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
	show_fps(game);
	game->shoot_timer += g_delta_time;
	return (0);
}

int	update(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_clear_window(game->mlx, game->win);
	set_delta_time(game);
	limit_fps(120.0);
	if (game->state == MAIN_MENU)
		show_main_menu(game);
	else if (game->state == IN_GAME)
		game_loop(game);
	else if (game->state == IN_SETTINGS)
		show_settings(game);
	free(game->fps);
	game->fps = NULL;
	return (0);
}
