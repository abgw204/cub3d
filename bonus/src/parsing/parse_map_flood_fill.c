/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_flood_fill.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 16:30:11 by vfidelis          #+#    #+#             */
/*   Updated: 2026/01/09 19:04:37 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	insert_in_matrix(char **matrix, int i, size_t *linear_pos)
{
	size_t	j;
	
	j = 1;
	matrix[i][0] = 'X';
	while ((*linear_pos) <= ft_strlen(get_data()->map))
	{
		if ((int)((*linear_pos) + 1) % get_data()->map_w == 0)
		{
			matrix[i][j++] = get_data()->map[(*linear_pos)];
			matrix[i][j] = 'X';
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
	matrix = ft_calloc(sizeof(char *), (get_data()->map_h + 3));
	while (i < (size_t)(get_data()->map_h + 2))
	{
		matrix[i] = ft_calloc(get_data()->map_w + 5, sizeof(char));     
		if (i > 0 && i < (size_t)(get_data()->map_h + 1))
			insert_in_matrix(matrix, i, &linear_pos);
		else
			ft_memset(matrix[i], 'X', get_data()->map_w + 2);
		i++;
	}
	return (matrix);
}

void	ft_flood_fill(char **map, int x, int y, int *valid_map)
{
	if (x < 0 || y < 0 || x >= get_data()->map_h + 2 || y >= get_data()->map_w + 2)
		return ;
	if (map[x][y] == '0')
	{
		*valid_map = 1;
		return ;
	}
	if (map[x][y] == '1' || map[x][y] == 'Y')
		return ;
	map[x][y] = 'Y';
	ft_flood_fill(map, x - 1, y, valid_map);
	ft_flood_fill(map, x + 1, y, valid_map);
	ft_flood_fill(map, x, y - 1, valid_map);
	ft_flood_fill(map, x, y + 1, valid_map);
	
}

//int	main()
//{
//	char **matrix = fill_in_with_x();
//}