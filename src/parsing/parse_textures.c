/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:00:22 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/24 18:01:35 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	free_all(char **textures_matrix, char ***textures_array)
{
	free_stack_matrix_array(textures_array);
	free_matrix(textures_matrix);
	return (print_error("Wrong textures in the config file!"));
}

static char	**parse_texture(char *texture, int i)
{
	char **matrix;

	matrix = ft_split(texture, ' ');
	if (!matrix)
		return (NULL);
	if (ft_strlen(matrix[0]) == 2 && matrix[1] && matrix[1][0] != '\n')
	{
		if (matrix[0][0] == 'N' && matrix[0][1] == 'O'
			&& i == 0)
			return (matrix);
		else if (matrix[0][0] == 'S' && matrix[0][1] == 'O'
			&& i == 1)
			return (matrix);
		else if (matrix[0][0] == 'W' && matrix[0][1] == 'E'
			&& i == 2)
			return (matrix);
		else if (matrix[0][0] == 'E' && matrix[0][1] == 'A'
			&& i == 3)
			return (matrix);
	}
	free_matrix(matrix);
	return (NULL);
}

int	parse_textures(int map_fd, char **textures, int i)
{
	textures = (char **)ft_calloc(5 * sizeof(char *), 1);
	if (!textures)
		return (print_error("malloc error!"));
	initialize_matrix(textures, 5);
	while (i < 4)
	{
		textures[i] = get_next_line(map_fd);
		if (textures[i])
		{
			if (textures[i][0] == '\n')
			{
				free(textures[i]);
				textures[i] = NULL;
				continue ;
			}
			get_data()->textures[i] = parse_texture(textures[i], i);
			if (!get_data()->textures[i])
				return (free_all(textures, get_data()->textures));
		}
		else
			return (free_all(textures, get_data()->textures));
		i++;
	}
	free_matrix(textures);
	return (0);
}

