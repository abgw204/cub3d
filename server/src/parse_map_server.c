/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_server.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 11:20:16 by gada-sil          #+#    #+#             */
/*   Updated: 2025/12/10 15:00:33 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server.h"

static char	*linearize_map(t_list *list, t_server *s)
{
	char		*map;
	char		*line;
	uint32_t	line_diff;
	uint32_t	line_len;
	uint32_t	max_w;

	max_w = s->map_w;
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

static int	get_map(int file_fd, t_server *s)
{
    char	*line;

    line = NULL;
	s->map_list = ft_lstnew(line);
	if (search_bigger(line, &s->map_w))
		return (error(line, s->map_list, "Newline in map!"));
    free(line);
    line = get_next_line(file_fd);
    while (line)
    {
    	if (search_bigger(line, &s->map_w))
		{
			free(line);
			line = jump_blank_lines(&file_fd);
			if (line)
				return (error(line, s->map_list, "Newline in map!"));
		}
        ft_lstadd_back(&s->map_list, ft_lstnew(line));
		free(line);
		line = get_next_line(file_fd);
    }
	s->map_h = ft_lstsize(s->map_list);
    return (0);
}

int	parse_map_s(t_server *s, char *file)
{
    int	file_fd;

	printf("%s\n", file);
    file_fd = open(file, O_RDONLY);
	if (file_fd == -1)
	{
		perror("file");
		return (1);
	}
	if (get_map(file_fd, s))
		return (1);
	trim_newlines_map(s->map_list);
	// if (expand_map(get_data()->map_list))
		// return (1);
	s->map = linearize_map(s->map_list, s);
	ft_lstclear(&s->map_list, free);
	return (0);
}