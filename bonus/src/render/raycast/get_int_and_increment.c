/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_int_and_increment.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 12:18:38 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/12 19:20:12 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int	get_int_and_increment(pthread_mutex_t *mutex, int *variable)
{
	int	ret;

	pthread_mutex_lock(mutex);
	ret = *variable;
	(*variable)++;
	pthread_mutex_unlock(mutex);
	return (ret);
}
