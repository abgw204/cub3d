/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_matrix.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:27:47 by gada-sil          #+#    #+#             */
/*   Updated: 2024/12/29 19:41:52 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**create_matrix(int rows, int cols)
{
	char	**matrix;
	int		i;
	int		j;

	i = 0;
	j = 0;
	matrix = (char **)malloc(rows * sizeof(char *));
	if (!matrix)
		free(matrix);
	while (i < rows)
	{
		matrix[i] = (char *)malloc(cols * sizeof(char));
		if (!matrix[i])
		{
			while (j <= i)
				free(matrix[j++]);
			free(matrix);
			return (NULL);
		}
		i++;
	}
	return (matrix);
}
