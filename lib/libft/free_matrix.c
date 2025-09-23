/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:54:42 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/23 19:05:01 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	free_matrix(char **matrix, int size)
{
    int	i;
	
	i = 0;
	if (size == -1)
	{
		while (matrix[i])
		free(matrix[i++]);
		
	}
	else
	{
		while (i < size)
		free(matrix[i++]);
	}
	free(matrix);
	return (1);
}