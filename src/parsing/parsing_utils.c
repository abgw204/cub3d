/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:01:51 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/24 17:35:26 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	free_stack_matrix_array(char ***arr)
{
	int	i;

	i = 0;
	if (!arr || !*arr)
		return ;
	while (arr[i])
		free_matrix(arr[i++]);
}

void	initialize_matrix(char **matrix, int size)
{
	int	i;

	i = 0;
	while (i < size)
		matrix[i++] = NULL;
}