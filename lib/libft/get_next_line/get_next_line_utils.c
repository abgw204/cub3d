/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:53:17 by gada-sil          #+#    #+#             */
/*   Updated: 2025/05/08 19:47:52 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc_gnl(size_t num, size_t size)
{
	void			*ptr;
	size_t			total_size;
	size_t			i;
	unsigned char	*str;

	i = 0;
	if (num != 0 && (num * size) / num != size)
		return (NULL);
	total_size = num * size;
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	str = (unsigned char *)ptr;
	while (i < total_size)
		str[i++] = '\0';
	return (ptr);
}

char	*ft_strchr_gnl(const char *s1, int c)
{
	while (*s1)
	{
		if ((unsigned char)*s1 == (unsigned char)c)
			return ((char *)s1);
		s1++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)s1);
	return (0);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*ptr;
	size_t	i;
	size_t	j;

	s1_len = ft_strlen_gnl(s1);
	s2_len = ft_strlen_gnl(s2);
	i = 0;
	j = 0;
	ptr = (char *)malloc(s1_len + s2_len + 2);
	if (!ptr)
		return (NULL);
	while (s1[j])
		ptr[i++] = s1[j++];
	if (s1[j - 1] != ' ')
		ptr[i++] = ' ';
	while (*s2)
		ptr[i++] = *s2++;
	ptr[i] = '\0';
	return (ptr);
}

size_t	ft_strlen_gnl(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
