/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 11:21:26 by gada-sil          #+#    #+#             */
/*   Updated: 2024/09/25 14:27:18 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*str;
	size_t				i;

	str = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (*str == (unsigned char)c)
			return ((void *)str);
		str++;
		i++;
	}
	return (NULL);
}
/*#include <stdio.h>
int	main()
{
	char s1[] = "";
	char s2[] = "";
	char *teste;
	char *teste2;

	teste = ft_memchr(s1, '.', 10);
	teste2 = memchr(s2, '.', 10);

	printf("%s\n", teste);
	printf("%s\n", teste2);
}*/
