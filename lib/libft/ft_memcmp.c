/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:45:05 by gada-sil          #+#    #+#             */
/*   Updated: 2024/09/27 17:15:14 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned const char	*ptr1;
	unsigned const char	*ptr2;
	size_t				i;

	ptr1 = (unsigned const char *)s1;
	ptr2 = (unsigned const char *)s2;
	i = 0;
	while (i < n)
	{
		if (ptr1[i] != ptr2[i])
			return (ptr1[i] - ptr2[i]);
		i++;
	}
	return (0);
}
/*#include <stdio.h>
int	main()
{
	//int	s1[3] = {1, 2, 3};
	//char	s2[] = "i'm a f***ing idiot";

	//int	s3[3] = {1, 2, 3};
	//char	s3[] = "hello my name is kyle";
	//char	s4[] = "i'm a f***ing idiot";

	//printf("%d\n", ft_memcmp(s1, s2, 3));
	//printf("%d\n", memcmp(s3, s4, 3));
	char s[] = {-128, 0, 127, 0};
	char s2[] = {0, 0, 127, 0};
	//printf("%d", memcmp(s, s2, 0));
	printf("%d", ft_memcmp(s, s2, 0));
}*/
