/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delta_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:58 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/24 17:05:59 by gada-sil         ###   ########.fr       */
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

static char	*get_fps_str(int frames, double fps_timer)
{
	char	*res;
	char	*fps;
	
	if (fps_timer > 0.000001)
		fps = ft_itoa((int)(frames / fps_timer));
	else
		fps = ft_strdup("00");
	res = ft_strjoin("FPS: ", fps);
	free(fps);
	return (res);
}

void	set_delta_time(t_game *game)
{
	static double	last_time = 0.0;
	static double	fps_timer = 0.0;
	static int		frames = 0;
	double			current_time = get_time_in_seconds();
	char			*fps;

	g_delta_time = current_time - last_time;
	if (last_time == 0)
		g_delta_time = 0;
	last_time = current_time;
	if (game->game_config.show_fps)
	{
		frames++;
		fps_timer += g_delta_time;
		if (fps_timer >= 1.0)
		{
			frames = 0;
			fps_timer = 0.0;
		}
		fps = get_fps_str(frames, fps_timer);
		mlx_string_put(game->mlx, game->win, SCREEN_WIDTH - (SCREEN_WIDTH - 30),
			SCREEN_HEIGHT - (SCREEN_HEIGHT - 30), 0xFFFFFF, fps);
		free(fps);
	}
}
