/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_flood_fill.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:30:11 by vfidelis          #+#    #+#             */
/*   Updated: 2025/11/25 14:07:46 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	insert_in_matrix(char **matrix, int i, size_t *linear_pos)
{
	size_t	j;
	
	j = 0;
	matrix[i][j++] = 'X';
	while ((*linear_pos) < ft_strlen(get_data()->map))
	{
		if ((int)((*linear_pos) + 1) % get_data()->map_w == 0)
		{
			matrix[i][j++] = 'X';
			(*linear_pos)++;
			break ;
		}
		if (get_data()->map[(*linear_pos)] == ' ')
			matrix[i][j++] = 'X';
		else
			matrix[i][j++] = get_data()->map[(*linear_pos)];
		(*linear_pos)++;
	}
}
char	**fill_in_with_x(void)
{
	size_t	i;
	char	**matrix;
	size_t	linear_pos;

	linear_pos = 0;
	i = 0;
	matrix = malloc(sizeof(char *) * (get_data()->map_h + 2));
	matrix[get_data()->map_h + 2] = NULL;
	while (i < (size_t)(get_data()->map_h + 2))
	{
		matrix[i] = ft_calloc(get_data()->map_w + 2, sizeof(char));     
		if (i > 0 && i < (size_t)(get_data()->map_h + 1))
			insert_in_matrix(matrix, i, &linear_pos);
		else
			ft_memset(matrix[i], 'X', get_data()->map_w + 1);
		i++;
	}
	return (matrix);
}

/*int	flood_fill()
{
	char **map;

	map = fill_in_with_x();
	
	
}*/

//int	main()
//{
//	char **matrix = fill_in_with_x();
//}