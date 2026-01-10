/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:54:32 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/10 14:00:20 by vfidelis         ###   ########.fr       */
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

int	thread_create(pthread_t *thread, void *(func)(void *), void *data)
{
	if (pthread_create(thread, NULL, func, data) != 0)
		return (print_error("A Thread failed to be created!\n"));
	return (0);
}

int	game_loop(t_game *game)
{
	int	i;

	i = 0;
	move_player(game);
	start_all_render_threads(&game->cond_start, &game->m);
	wait_all_render_threads(&game->cond_done, &game->m);
	while (i < game->doors_n)
		update_door(&game->doors[i++], g_delta_time, game, 0.0);
	raycast_door(game);
	draw_sprites(game);
	draw_crosshair(&game->screen);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
	draw_minimap(game);
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
