/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   limit_fps.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:58 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/24 17:05:59 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	isleep(double time)
{
	double	start;

	start = get_time_in_seconds() + time;
	while (get_time_in_seconds() < start)
		;
}

void    limit_fps(double target_fps)
{
    static double	last = 0.0;
    double			now;
    double			frame_time;
    double			elapsed;

	now = get_time_in_seconds();
	frame_time = 1.0 / target_fps;
	elapsed = now - last;
    if (elapsed < frame_time)
        isleep((frame_time - elapsed));
    last = get_time_in_seconds();
}
