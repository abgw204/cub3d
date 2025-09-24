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

double	delta_time = 0.0;

static double	get_time_in_seconds(void)
{
	struct timeval	tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

void	set_delta_time(void)
{
	static double	last_time = 0.0;
	double	current_time = get_time_in_seconds();

	delta_time = current_time - last_time;
	if (last_time == 0)
		delta_time = 0;
	last_time = current_time;
}
