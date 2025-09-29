/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 19:14:13 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/29 20:30:29 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char    *jump_blank_lines(int *file_fd)
{
    char    *line;

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

int parse_map(int file_fd)
{
    t_list  *map;
    char    *line;
    
    line = jump_blank_lines(&file_fd);
    if (!line)
        return (print_error("No map found!"));
}