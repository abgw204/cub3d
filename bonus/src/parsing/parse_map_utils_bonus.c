/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:54:41 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/24 15:38:55 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

static int	compare(char c, char *valids)
{
	int	invalid;

	invalid = 1;
	while (*valids)
	{
		if (c == *valids)
			invalid = 0;
		valids++;
	}
	return (invalid);
}

int	check_valid(char *line, char *valids)
{
	while (*line)
	{
		if (compare(*line, valids))
			return (0);
		line++;
	}
	return (1);
}

int	error(char *line, t_list *list, char *error_message)
{
	if (line)
		free(line);
	ft_lstclear(&list, free);
	return (free_all(NULL, get_data()->config, error_message));
}

char	*jump_blank_lines(int *file_fd)
{
	char	*line;

	while (1337)
	{
		line = get_next_line(*file_fd);
		if (!line)
			break ;
		if (line[0] == '\n')
		{
			free(line);
			continue ;
		}
		return (line);
	}
	return (NULL);
}

int	search_bigger(char *line, int *w)
{
	int	len;

	if (line && line[0] == '\n')
		return (1);
	len = ft_strlen(line);
	if (*w < len)
	{
		if (line[len - 1] == '\n')
			*w = (int)len - 1;
		else
			*w = (int)len;
	}
	return (0);
}
