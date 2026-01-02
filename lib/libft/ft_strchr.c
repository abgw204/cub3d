/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:21:26 by gada-sil          #+#    #+#             */
/*   Updated: 2024/09/25 14:27:18 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s1, int c)
{
	size_t	i;

	i = 0;
	while (s1[i])
	{
		if ((unsigned char)s1[i] == (unsigned char)c)
			return ((char *)&s1[i]);
		i++;
	}
	if (c == 0)
		return ((char *)&s1[i]);
	return (0);
}
/*#include <stdio.h>
int main()
{
	char s1[] = "testing";
	char s2[] = "testing";
	printf("%s\n", ft_strchr(s1, 't'));
	printf("%s\n", strchr(s2, 't'));
}*/
