/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:54:32 by gada-sil          #+#    #+#             */
/*   Updated: 2025/11/07 08:29:15 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	clear_screen_image(t_game *game)
{
	memset(game->screen.addr, 0, SCREEN_WIDTH * SCREEN_HEIGHT * 4);
}

void	draw_crosshair(t_image *screen)
{
	t_uiv2	pos;

	pos.x = SCREEN_WIDTH / 2 - 4;
	pos.y = SCREEN_HEIGHT / 2 - 4;
	draw_circle(pos, 3, 0xFFFFFF, screen);
}

void	thread_create(pthread_t *thread, void *(func)(void *), void *data)
{
	if (pthread_create(thread, NULL, func, data) != 0)
		print_error("A Thread failed to be created!\n");
}

int game_loop(t_game *game)
{
	clear_screen_image(game);
    rotate_camera(game);
    move_player(game);
	calculate_sprites(game);
	start_all_render_threads(&game->cond_start, &game->m);
	wait_all_render_threads(&game->cond_done, &game->m);
	calculate_sprites(game);
	draw_crosshair(&game->screen);
    mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
    if (game->config.show_fps && game->fps)
    {
        mlx_string_put(game->mlx, game->win, SCREEN_WIDTH - (SCREEN_WIDTH - 30),
		SCREEN_HEIGHT - (SCREEN_HEIGHT - 30), 0xFFFFFF, game->fps);
    }
	draw_minimap(game);
    return (0);
}

int	update(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	mlx_clear_window(game->mlx, game->win);
	set_delta_time(game);
	limit_fps(300.0);
	if (game->state == MAIN_MENU)
    {
        enable_mouse(game);
		show_main_menu(game);
    }
	else if (game->state == IN_GAME)
    {
        disable_mouse(game);
		game_loop(game);
    }
	else if (game->state == IN_SETTINGS)
		show_settings(game);
	free(game->fps);
    game->fps = NULL;
	return (0);
}
