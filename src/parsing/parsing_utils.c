/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:01:51 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/30 15:57:58 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	trim_newlines_map(t_list *map)
{
	char	*temp;

	while (map)
	{
		temp = map->content;
		map->content = ft_strtrim(temp, "\n");
		free(temp);
		map = map->next;
	}	
}

void	trim_newline_chars(char ***config)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (config[i])
	{
		while (config[i][j])
		{
			if (config[i][j + 1] == NULL)
			{
				temp = config[i][j];
				config[i][j] = ft_strtrim(temp, "\n");
				free(temp);
			}
			j++;
		}
		j = 0;
		i++;
	}
}

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
