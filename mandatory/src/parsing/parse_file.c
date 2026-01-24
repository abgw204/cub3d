/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:00:22 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/10 11:41:23 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	check_commas_number(char *str)
{
	int	n;

	n = 0;
	while (*str)
	{
		if (*str == ',')
			n++;
		str++;
	}
	if (n != 2)
		return (1);
	return (0);
}

static int	check_double_comma(char *str)
{
	char	*pos;

	pos = ft_strchr(str, ',');
	while (pos)
	{
		if (*(pos + 1) == ',')
			return (1);
		pos = ft_strchr(pos + 1, ',');
	}
	return (0);
}

static char	**parse_symbol(char *str, char **symbols)
{
	char	**matrix;
	int		len;

	matrix = ft_split(str, " ");
	if (!matrix)
		return (NULL);
	len = ft_strlen(matrix[0]);
	if (len == 2)
	{
		if (compare_symbols(matrix[0], symbols))
			return (matrix);
	}
	else if (len == 1)
	{
		free_matrix(matrix);
		if (check_double_comma(str) || check_commas_number(str))
			return (NULL);
		matrix = ft_split(str, " ,");
		if (compare_symbols(matrix[0], symbols))
			return (matrix);
	}
	free_matrix(matrix);
	return (NULL);
}

int	parse_file(int map_fd, char **config, char **symbols, int i)
{
	char	**temp;

	while (i < CONFIG_TOKENS)
	{
		config[i] = get_next_line(map_fd);
		if (config[i])
		{
			if (config[i][0] == '\n')
			{
				free(config[i]);
				config[i] = NULL;
				continue ;
			}
			temp = parse_symbol(config[i], symbols);
			get_data()->config[i] = temp;
			if (!get_data()->config[i])
				return (free_all(config, get_data()->config,
						"Wrong config in file!"));
		}
		else
			return (free_all(config, get_data()->config, "Few lines in file!"));
		i++;
	}
	free_matrix(config);
	return (0);
}
