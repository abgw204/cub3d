/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 15:44:04 by gada-sil          #+#    #+#             */
/*   Updated: 2024/10/01 15:44:05 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*ptr;
	char			*str;

	i = 0;
	str = (char *)s;
	ptr = (char *)malloc(ft_strlen(str) + 1);
	if (!ptr)
		return (NULL);
	while (str[i])
	{
		ptr[i] = f(i, str[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
/*char	toUPPER(unsigned int i, char s)
{
	unsigned int a;

	a = i;
	a = a + 1;
	s = toupper(s);
	return (s);
}
#include <stdio.h>
int	main()
{
	char str[] = "oiiiiii";
	char *s = ft_strmapi(str, toUPPER);
	printf("%s", s);
	return 0;
}*/
