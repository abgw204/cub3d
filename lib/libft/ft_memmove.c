/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:43:20 by gada-sil          #+#    #+#             */
/*   Updated: 2024/09/25 14:49:50 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*src2;
	unsigned char		*dest2;

	src2 = (const unsigned char *) src;
	dest2 = (unsigned char *) dest;
	if (dest2 == NULL || src2 == NULL)
		return (NULL);
	if (dest < src)
		return (ft_memcpy(dest, src, n));
	while (n-- > 0)
		dest2[n] = src2[n];
	return (dest);
}
/*#include <stdio.h>
int	main(void)
{
	char oi1[] = "hello";
	char oi2[] = "ooooo";
	char	*oi_final = ft_memmove(oi1, oi2, 5);
	//char	*oi_final2 = memmove(oi1, oi2, 5);
	printf("%s", oi_final);
}*/
