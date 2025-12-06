/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:02:43 by gada-sil          #+#    #+#             */
/*   Updated: 2025/12/04 16:45:20 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server.h"

double			g_delta_time = 0.0;
double			acumulator = 0.0;
const double	tick_time = 1.0 / 128.0;

static double	get_time_in_seconds(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec + tv.tv_usec / 1000000.0);
}

void	set_server_delta_time(void)
{
	static double	last = 0.0;
	double			current_time;

	current_time = get_time_in_seconds();
	g_delta_time = current_time - last;
	if (last == 0)
		g_delta_time = 0;
	last = current_time;
}
