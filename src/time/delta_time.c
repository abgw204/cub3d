/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delta_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:58 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/29 18:47:52 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

double	g_delta_time = 0.0;

double	get_time_in_seconds(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

static void	print_fps(t_game *game, int frames, double fps_timer)
{
	char	*res;
	char	*fps;
	
	if (fps_timer > 0.000001)
		fps = ft_itoa((int)(frames / fps_timer));
	else
		fps = ft_strdup("00");
	res = ft_strjoin("FPS: ", fps);
	mlx_string_put(game->mlx, game->win, SCREEN_WIDTH - (SCREEN_WIDTH - 30),
		SCREEN_HEIGHT - (SCREEN_HEIGHT - 30), 0xFFFFFF, res);
	free(fps);
	free(res);

	// DEBUG INFO

	/*mlx_string_put(game->mlx, game->win, SCREEN_WIDTH - (SCREEN_WIDTH - 30),
		SCREEN_HEIGHT - (SCREEN_HEIGHT - 60), 0xFFFFFF, game->data->config[0][0]);
	mlx_string_put(game->mlx, game->win, SCREEN_WIDTH - (SCREEN_WIDTH - 46),
		SCREEN_HEIGHT - (SCREEN_HEIGHT - 60), 0xFFFFFF, game->data->config[0][1]);
	mlx_string_put(game->mlx, game->win, SCREEN_WIDTH - (SCREEN_WIDTH - 30),
		SCREEN_HEIGHT - (SCREEN_HEIGHT - 80), 0xFFFFFF, game->data->config[1][0]);
	mlx_string_put(game->mlx, game->win, SCREEN_WIDTH - (SCREEN_WIDTH - 46),
		SCREEN_HEIGHT - (SCREEN_HEIGHT - 80), 0xFFFFFF, game->data->config[1][1]);
	mlx_string_put(game->mlx, game->win, SCREEN_WIDTH - (SCREEN_WIDTH - 30),
		SCREEN_HEIGHT - (SCREEN_HEIGHT - 100), 0xFFFFFF, game->data->config[2][0]);
	mlx_string_put(game->mlx, game->win, SCREEN_WIDTH - (SCREEN_WIDTH - 46),
		SCREEN_HEIGHT - (SCREEN_HEIGHT - 100), 0xFFFFFF, game->data->config[2][1]);
	mlx_string_put(game->mlx, game->win, SCREEN_WIDTH - (SCREEN_WIDTH - 30),
		SCREEN_HEIGHT - (SCREEN_HEIGHT - 120), 0xFFFFFF, game->data->config[3][0]);
	mlx_string_put(game->mlx, game->win, SCREEN_WIDTH - (SCREEN_WIDTH - 46),
		SCREEN_HEIGHT - (SCREEN_HEIGHT - 120), 0xFFFFFF, game->data->config[3][1]);
	mlx_string_put(game->mlx, game->win, SCREEN_WIDTH - (SCREEN_WIDTH - 30),
		SCREEN_HEIGHT - (SCREEN_HEIGHT - 140), 0xFFFFFF, game->data->config[4][0]);
	mlx_string_put(game->mlx, game->win, SCREEN_WIDTH - (SCREEN_WIDTH - 46),
		SCREEN_HEIGHT - (SCREEN_HEIGHT - 140), 0xFF0000, game->data->config[4][1]);
	mlx_string_put(game->mlx, game->win, SCREEN_WIDTH - (SCREEN_WIDTH - 75),
		SCREEN_HEIGHT - (SCREEN_HEIGHT - 140), 0x00FF00, game->data->config[4][2]);
	mlx_string_put(game->mlx, game->win, SCREEN_WIDTH - (SCREEN_WIDTH - 100),
		SCREEN_HEIGHT - (SCREEN_HEIGHT - 140), 0x6666FF, game->data->config[4][3]);
	mlx_string_put(game->mlx, game->win, SCREEN_WIDTH - (SCREEN_WIDTH - 30),
		SCREEN_HEIGHT - (SCREEN_HEIGHT - 160), 0xFFFFFF, game->data->config[5][0]);
	mlx_string_put(game->mlx, game->win, SCREEN_WIDTH - (SCREEN_WIDTH - 46),
		SCREEN_HEIGHT - (SCREEN_HEIGHT - 160), 0xFF0000, game->data->config[5][1]);
	mlx_string_put(game->mlx, game->win, SCREEN_WIDTH - (SCREEN_WIDTH - 75),
		SCREEN_HEIGHT - (SCREEN_HEIGHT - 160), 0x00FF00, game->data->config[5][2]);
	mlx_string_put(game->mlx, game->win, SCREEN_WIDTH - (SCREEN_WIDTH - 100),
		SCREEN_HEIGHT - (SCREEN_HEIGHT - 160), 0x6666FF, game->data->config[5][3]);*/
}

void	set_delta_time(t_game *game)
{
	static double	last_time = 0.0;
	static double	fps_timer = 0.0;
	static int		frames = 0;
	double			current_time;

	current_time = get_time_in_seconds();
	g_delta_time = current_time - last_time;
	if (last_time == 0)
		g_delta_time = 0;
	last_time = current_time;
	if (game->config.show_fps)
	{
		frames++;
		fps_timer += g_delta_time;
		if (fps_timer >= 1.0)
		{
			frames = 0;
			fps_timer = 0.0;
		}
		print_fps(game, frames, fps_timer);
	}
}
