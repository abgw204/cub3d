/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:53:01 by gada-sil          #+#    #+#             */
/*   Updated: 2025/05/08 19:56:28 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*get_rest(char *buffer)
{
	int		line_len;
	int		j;
	char	*rest;

	line_len = 0;
	while (buffer[line_len] && buffer[line_len] != '\n')
		line_len++;
	if (!buffer[line_len])
	{
		free(buffer);
		return (NULL);
	}
	rest = ft_calloc_gnl((ft_strlen_gnl(buffer) - line_len + 1), sizeof(char));
	line_len++;
	j = 0;
	while (buffer[line_len])
		rest[j++] = buffer[line_len++];
	free(buffer);
	return (rest);
}

char	*join(char *buffer, char *temp)
{
	char	*full;

	full = ft_strjoin_gnl(buffer, temp);
	if (buffer)
		free(buffer);
	return (full);
}

static char	*get_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		line = ft_calloc_gnl(i + 2, sizeof(char));
	else
		line = ft_calloc_gnl(i + 1, sizeof(char));
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] && buffer[i] == '\n')
		line[i++] = '\n';
	return (line);
}

static char	*reading(int fd, char *buffer)
{
	char	*temp;
	int		bytes_read;

	if (!buffer)
		buffer = ft_calloc_gnl(1, 1);
	temp = ft_calloc_gnl(BUFFER_SIZE + 1, sizeof(char));
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(temp);
			free(buffer);
			return (NULL);
		}
		temp[bytes_read] = '\0';
		buffer = join(buffer, temp);
		if (ft_strchr_gnl(buffer, '\n'))
			break ;
	}
	free(temp);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*return_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = reading(fd, buffer);
	if (!buffer)
		return (NULL);
	return_line = get_line(buffer);
	buffer = get_rest(buffer);
	return (return_line);
}
