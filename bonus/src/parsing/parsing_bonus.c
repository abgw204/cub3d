/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:06 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/24 15:38:59 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

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

static int	validate_parameters_number(char ***config)
{
	while (*config)
	{
		if (ft_strlen(**config) == 2)
		{
			if (ft_len_matrix(*config) != 2)
				if (!(ft_len_matrix(*config) == 3
						&& !ft_strcmp((*config)[2], "\n")))
					return (print_error("Texture with invalid parameters!"));
		}
		else
		{
			if (ft_len_matrix(*config) != 4)
				if (!(ft_len_matrix(*config) == 5
						&& !ft_strcmp((*config)[4], "\n")))
					return (print_error("Color with invalid paramenters!"));
		}
		config++;
	}
	return (0);
}

static int	validate_config(int file_fd)
{
	char	**file;
	char	**possible_symbols;

	file = NULL;
	get_data()->config[6] = NULL;
	possible_symbols = create_symbols_matrix();
	if (!possible_symbols)
		return (print_error("Memory allocation error!"));
	file = (char **)ft_calloc((CONFIG_TOKENS + 1) * sizeof(char *), 1);
	if (!file)
	{
		free_matrix(possible_symbols);
		return (print_error("Memory allocation error!"));
	}
	initialize_matrix(file, CONFIG_TOKENS + 1);
	if (parse_file(file_fd, file, possible_symbols, 0))
		return (free_matrix(possible_symbols));
	if (validate_parameters_number(get_data()->config))
		return (free_all(possible_symbols, get_data()->config, NULL));
	free_matrix(possible_symbols);
	return (0);
}

int	parse_given_file(char *file)
{
	int	file_fd;

	if (invalid_extension(file))
		return (print_error("Invalid file extension!"));
	file_fd = open(file, O_RDONLY);
	if (file_fd < 0)
		return (print_perror());
	if (validate_config(file_fd))
		return (close_fd(file_fd));
	if (parse_fc_colors(get_data()->config))
		return (close_fd(file_fd));
	trim_newline_chars(get_data()->config);
	if (parse_map(file_fd))
		return (close_fd(file_fd));
	close(file_fd);
	return (0);
}
