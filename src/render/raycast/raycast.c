/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:39:15 by gada-sil          #+#    #+#             */
/*   Updated: 2025/11/07 08:29:41 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void    *raycast(void *param)
{
	t_raycast	raycast;
	t_game		*game;
	int			id;
	int			start;
	int			limit;

	game = (t_game *)param;
	id = get_int_and_increment(&game->m, &game->id);
	start = id * (SCREEN_WIDTH / N_THREADS);
	limit = (id + 1) * (SCREEN_WIDTH / N_THREADS);
	if (id == N_THREADS - 1)
		limit = SCREEN_WIDTH;
	printf("thread %d start=%d end=%d\n", id, start, limit - 1);
	sleep(1);
	exit(EXIT_FAILURE);
	while (true)
	{
		wait_signal_from_main_thread(&game->cond_start, &game->m);
		while (start < limit)
			cast_rays_and_draw(&raycast, game, &start);
		increment_int(&game->m, &game->threads_done);
		if (get_int(&game->m, &game->threads_done) == N_THREADS)
		{
			set_int(&game->m, &game->threads_done, 0);
			send_signal_to_main_thread(&game->cond_done, &game->m);
		}
		start = id * (SCREEN_WIDTH / N_THREADS);
	}
	return (NULL);
}
