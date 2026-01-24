/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_cond_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 18:39:15 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/24 15:39:53 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d_bonus.h"

void	send_signal_to_main_thread(pthread_cond_t *done, pthread_mutex_t *m)
{
	pthread_mutex_lock(m);
	pthread_cond_signal(done);
	pthread_mutex_unlock(m);
}

void	wait_signal_from_main_thread(pthread_cond_t *start, pthread_mutex_t *m)
{
	pthread_mutex_lock(m);
	pthread_cond_wait(start, m);
	pthread_mutex_unlock(m);
}

void	start_all_render_threads(pthread_cond_t *start, pthread_mutex_t *m)
{
	pthread_mutex_lock(m);
	pthread_cond_broadcast(start);
	pthread_mutex_unlock(m);
}

void	wait_all_render_threads(pthread_cond_t *done, pthread_mutex_t *m)
{
	pthread_mutex_lock(m);
	pthread_cond_wait(done, m);
	pthread_mutex_unlock(m);
}
