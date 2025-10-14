/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:14:13 by gada-sil          #+#    #+#             */
/*   Updated: 2025/10/14 15:56:45 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	check_invalid_chars(t_list *map)
{
	t_list	*temp;

	temp = map;
	while (temp)
	{
		if (!check_valid(temp->content, "01NSWE "))
			return (error(NULL, map, "Invalid character in map!"));
		temp = temp->next;
	}
	return (0);
}

static int	get_map(int file_fd)
{
    char	*line;

    line = jump_blank_lines(&file_fd);
	if (!line)
    	return (free_all(NULL, get_data()->config, "No map found!"));
	get_data()->map_list = ft_lstnew(line);
	if (search_bigger(line, &get_data()->map_w))
		return (error(line, get_data()->map_list, "Newline in map!"));
    free(line);
    line = get_next_line(file_fd);
    while (line)
    {
    	if (search_bigger(line, &get_data()->map_w))
		{
			free(line);
			line = jump_blank_lines(&file_fd);
			if (line)
				return (error(line, get_data()->map_list, "Newline in map!"));
		}
        ft_lstadd_back(&get_data()->map_list, ft_lstnew(line));
		free(line);
		line = get_next_line(file_fd);
    }
	get_data()->map_h = ft_lstsize(get_data()->map_list);
    return (0);
}

int	parse_map(int file_fd)
{
	if (get_map(file_fd))
		return (1);
	trim_newlines_map(get_data()->map_list);
	if (check_invalid_chars(get_data()->map_list))
		return (1);
	// if (count_map_chars(get_data()->map_list))
		// return (1);
	// if (expand_map(get_data()->map_list))
		// return (1);
	return (0);
}
