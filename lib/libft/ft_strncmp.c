/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:32:46 by gada-sil          #+#    #+#             */
/*   Updated: 2024/09/23 15:37:14 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*s;

	i = 0;
	s = (unsigned char *)s1;
	if (n == 0)
		return (0);
	while (s[i] != '\0' && s2[i] != '\0' && i < n - 1)
	{
		if (s[i] != s2[i])
			return (s[i] - s2[i]);
		i++;
	}
	return (s[i] - s2[i]);
}
/*#include <stdio.h>
int	main(void)
{	
	unsigned int	x;

	x = 5;
	printf("%d\n", ft_strncmp("test", "test", 6));
	printf("%d", strncmp("test", "test", 6));
	return (0);
}*/
