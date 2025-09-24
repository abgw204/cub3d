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

int	validate_map(int map_fd)
{
	char	**file[4];

	if (parse_textures(map_fd, file[0], 0))
		return (1);
	//if (parse_fc_colors(map_fd, file[1]))
	//	return (1);
	return (0);
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

int	parse_map_file(char *file)
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
