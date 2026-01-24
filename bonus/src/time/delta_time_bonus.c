/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delta_time_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:58 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/24 15:40:04 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

double	g_delta_time = 0.0;

double	get_time_in_seconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

static void	get_fps(t_game *game, int frames, double fps_timer)
{
	char	*fps;

	if (fps_timer > 0.000001)
		fps = ft_itoa((int)(frames / fps_timer));
	else
		fps = ft_strdup("00");
	game->fps = ft_strjoin("FPS: ", fps);
	free(fps);
}

void	set_delta_time(t_game *game)
{
	static double	last = 0.0;
	static double	fps_timer = 0.0;
	static int		frames = 0;
	double			current_time;

	current_time = get_time_in_seconds();
	g_delta_time = current_time - last;
	if (last == 0)
		g_delta_time = 0;
	last = current_time;
	if (game->config.show_fps)
	{
		frames++;
		fps_timer += g_delta_time;
		if (fps_timer >= 1.0)
		{
			frames = 0;
			fps_timer = 0.0;
		}
		get_fps(game, frames, fps_timer);
	}
}
