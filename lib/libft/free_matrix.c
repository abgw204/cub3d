/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_matrix.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 18:54:42 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/09 18:57:04 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	free_matrix(char **matrix)
{
    int	i;
	
	i = 0;
	if (!matrix || !*matrix)
		return (1);
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
	return (1);
}