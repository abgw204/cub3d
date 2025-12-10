/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:14:13 by gada-sil          #+#    #+#             */
/*   Updated: 2025/12/10 17:28:22 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static char	*linearize_map(t_list *list)
{
	char		*map;
	char		*line;
	uint32_t	line_diff;
	uint32_t	line_len;
	uint32_t	max_w;

	max_w = get_data()->map_w;
	map = NULL;
	while (list)
	{
		line_len = ft_strlen(list->content);
		line_diff = max_w - line_len;
		line = (char *)ft_calloc(1, line_len + line_diff + 1);
		ft_strlcpy(line, list->content, line_len + 1);
		while (line_len < max_w)
			line[line_len++] = 'X';
		map = join_free_both(map, line);
		list = list->next;
	}
	return (map);
}

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

static int	count_map_chars(t_list *map)
{
	int	i;
	int	letter;

	i = 0;
	letter = 0;
	while (map)
	{
		while (map->content[i])
		{
			if (map->content[i] == 'N' || map->content[i] == 'S'
				|| map->content[i] == 'W' || map->content[i] == 'E')
				letter++;
			i++;
		}
		i = 0;
		map = map->next;
	}
	if (letter > 1)
		return (error(NULL, get_data()->map_list, "Multiple players in map!"));
	else if (letter == 0)
		return (error(NULL, get_data()->map_list, "No player in map!"));
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
	if (count_map_chars(get_data()->map_list))
		return (1);
	// if (expand_map(get_data()->map_list))
		// return (1);
	get_data()->map = linearize_map(get_data()->map_list);
	ft_lstclear(&get_data()->map_list, free);
	//for (size_t i = 0;  i < ft_strlen(get_data()->map); i++)
	//{
	//	printf("%c", get_data()->map[i]);
	//	if ((int)(i + 1) % get_data()->map_w == 0)
	//		printf("\n");
	//}
	return (0);
}
