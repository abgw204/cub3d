/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delta_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:58 by gada-sil          #+#    #+#             */
/*   Updated: 2025/12/04 13:56:19 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

#include "raylib.h"

double	g_delta_time = 0.0;

double	get_time_in_seconds(void)
{
	return (GetTime());
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
	static double	fps_timer = 0.0;
	static int		frames = 0;

	// Use raylib frame timing for cross-platform support.
	g_delta_time = (double)GetFrameTime();
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

	(void)game;
}
