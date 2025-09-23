/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:34:52 by vfidelis          #+#    #+#             */
/*   Updated: 2024/11/05 18:38:11 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*line_break(char **buffer)
{
	char	*line;
	size_t	i;

	i = 0;
	while ((*buffer)[i] && (*buffer)[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	ft_memcpy(line, *buffer, i);
	if ((*buffer)[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	new_pos(buffer, *buffer + i);
	return (line);
}

void	reading(int fd, char **buffer, int *receiver)
{
	char	*str;

	if (!*buffer)
	{
		*buffer = (char *)malloc(1);
		(*buffer)[0] = '\0';
	}
	str = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (!ft_strchr(*buffer, '\n'))
	{
		*receiver = read(fd, str, BUFFER_SIZE);
		if (*receiver < 0)
		{
			free(str);
			free(*buffer);
			*buffer = NULL;
			return ;
		}
		if (*receiver == 0)
			break ;
		str[*receiver] = '\0';
		ft_realloc(buffer, str);
	}
	free(str);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	int			receiver;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	receiver = 0;
	reading(fd, &buffer, &receiver);
	if (receiver > 0 || (buffer && buffer[0] != '\0'))
		return (line_break(&buffer));
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}
	return (NULL);
}
/*
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("fd.txt", O_RDWR);
	line = (void *)1;
	for (int i = 0; line; i++)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}*/
