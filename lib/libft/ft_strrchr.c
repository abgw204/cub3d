/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:25:11 by gada-sil          #+#    #+#             */
/*   Updated: 2024/09/24 14:31:22 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int			i;

	i = ft_strlen(str);
	while (i >= 0)
	{
		if ((unsigned char)str[i] == (unsigned char)c)
			return ((char *)str + i);
		i--;
	}
	return (NULL);
}
/*#include <stdio.h>
int	main(void)
{
	printf("Theirs: %s\n", strrchr("iiiiii.oooooo.aaaaaaa.ppppp", 'a'));
	printf("Mine: %s", ft_strrchr("iiiiii.oooooo.aaaaaaa.ppppp", 'a'));
}*/
