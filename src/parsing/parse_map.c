/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:14:13 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/30 18:10:57 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	error(char *line, t_list *list)
{
	free(line);
	ft_lstclear(&list, free);
	return (free_all(NULL, get_data()->config,
	"New line character inside map!"));
}

static char	*jump_blank_lines(int *file_fd)
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

static int	search_bigger(char *line, int *w)
{
	int	len;
	
	len = ft_strlen(line);
	if (line && line[0] == '\n')
		return (1);
	if (*w < len)
	{
		if (line[len - 1] == '\n')
			*w = (int)len - 1;
		else
			*w = (int)len;
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
		return (error(line, get_data()->map_list));
    free(line);
    line = get_next_line(file_fd);
    while (line)
    {
    	if (search_bigger(line, &get_data()->map_w))
			return (error(line, get_data()->map_list));
        ft_lstadd_back(&get_data()->map_list, ft_lstnew(line));
		free(line);
		line = get_next_line(file_fd);
    }
	trim_newlines_map(get_data()->map_list);
	get_data()->map_h = ft_lstsize(get_data()->map_list);
    return (0);
}

int	parse_map(int file_fd)
{
	if (get_map(file_fd))
		return (1);	
	return (0);
}