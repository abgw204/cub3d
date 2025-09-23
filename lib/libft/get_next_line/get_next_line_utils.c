/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:34:55 by vfidelis          #+#    #+#             */
/*   Updated: 2025/09/23 16:26:41 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_realloc(char **str1, char *str2)
{
	char	*new_str;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(*str1);
	len2 = ft_strlen(str2);
	new_str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!new_str)
		return ;
	ft_memcpy(new_str, *str1, len1);
	ft_memcpy(new_str + len1, str2, len2);
	new_str[len1 + len2] = '\0';
	free(*str1);
	*str1 = new_str;
}

void	new_pos(char **buffer, char *pos)
{
	char	*temp;
	size_t	len;

	len = ft_strlen(pos);
	temp = (char *)malloc(sizeof(char) * (len + 1));
	if (!temp)
		return ;
	ft_memcpy(temp, pos, len);
	temp[len] = '\0';
	free(*buffer);
	*buffer = temp;
}
