/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters_setters.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 06:40:17 by gada-sil          #+#    #+#             */
/*   Updated: 2025/11/07 07:40:47 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	increment_int(pthread_mutex_t *mutex, int *value)
{
	pthread_mutex_lock(mutex);
	(*value)++;
	pthread_mutex_unlock(mutex);
}

void	set_double(pthread_mutex_t *mutex, double **variable, double value, int i)
{
	pthread_mutex_lock(mutex);
	(*variable)[i] = value;
	pthread_mutex_unlock(mutex);
}

bool	get_bool(pthread_mutex_t *mutex, bool *variable)
{
	bool	ret;

	pthread_mutex_lock(mutex);
	ret = *variable;
	pthread_mutex_unlock(mutex);
	return (ret);
}
int get_int(pthread_mutex_t *mutex, int *variable)
{
    int ret;

	pthread_mutex_lock(mutex);
	ret = *variable;
	pthread_mutex_unlock(mutex);
    return (ret);
}

void	set_int(pthread_mutex_t *mutex, int *variable, int value)
{
	pthread_mutex_lock(mutex);
	*variable = value;
	pthread_mutex_unlock(mutex);
}

long	get_int_and_increment(pthread_mutex_t *mutex, int *variable)
{
	long	ret;

	pthread_mutex_lock(mutex);
	ret = *variable;
    (*variable)++;
	pthread_mutex_unlock(mutex);
	return (ret);
}
