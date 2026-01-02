/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:38:02 by gada-sil          #+#    #+#             */
/*   Updated: 2024/09/25 12:09:55 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t size)
{
	size_t	i;
	size_t	k;
	char	*str;

	i = 0;
	k = 0;
	str = (char *)big;
	if (little[k] == '\0')
		return (str);
	while (str[i] != '\0' && i < size)
	{
		k = 0;
		while ((str[i + k] == little[k] && i + k < size) || little[k] == '\0')
		{
			if (little[k] == '\0')
				return (str + i);
			k++;
		}
		i++;
	}
	return (NULL);
}
/*#include <stdio.h>
int main()
{
	printf("%s", ft_strnstr("aaastaaaastaaaaateste123", "sta", 6));
}*/
