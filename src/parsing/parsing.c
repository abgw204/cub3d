/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:06 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/24 17:56:07 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static char	**create_symbols_matrix(void)
{
	char	**matrix;

	matrix = malloc(7 * sizeof(char *));
	if (!matrix)
		return (NULL);
	matrix[0] = ft_strdup("NO");
	matrix[1] = ft_strdup("SO");
	matrix[2] = ft_strdup("WE");
	matrix[3] = ft_strdup("EA");
	matrix[4] = ft_strdup("F");
	matrix[5] = ft_strdup("C");
	matrix[6] = NULL;
	return (matrix);
}

static int	invalid_extension(char *file)
{
	char	*dot;
	
	dot = ft_strrchr(file, '.');
	if (dot)
	{
		if (!ft_strcmp(++dot, "cub"))
			return (0);
	}
	return (1);
}

static int	validate_map(int map_fd)
{
	char	**file;
	char	**possible_symbols;

	file = NULL;
	get_data()->config[6] = NULL;
	possible_symbols = create_symbols_matrix();
	if (!possible_symbols)
		return (print_error("malloc error!"));
	if (parse_file(map_fd, file, possible_symbols, 0))
		return (free_matrix(possible_symbols));
	free_matrix(possible_symbols);
	return (0);
}

int	parse_given_file(char *file)
{
	int		map_fd;

	if (invalid_extension(file))
		return (print_error("Invalid file extension!"));
	map_fd = open(file, O_RDONLY);
	if (map_fd < 0)
		return (print_perror());
	if (validate_map(map_fd))
		return (1);
	return (0);
}
