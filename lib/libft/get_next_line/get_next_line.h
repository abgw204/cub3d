/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:34:44 by vfidelis          #+#    #+#             */
/*   Updated: 2025/09/23 16:25:50 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include "../../../include/libft.h"
# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
void	reading(int fd, char **buffer, int *receiver);
char	*line_break(char **buffer);
size_t	ft_strlen(const char *str);
void	ft_realloc(char **str1, char *str2);
void	new_pos(char **buffer, char *pos);
void	*ft_memcpy(void *dest, const void *src, size_t n);

#endif
