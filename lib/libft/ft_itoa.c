/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 12:45:05 by gada-sil          #+#    #+#             */
/*   Updated: 2024/09/27 17:15:14 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_int_min_and_0_fix(int n)
{
	char	*str;

	if (n == 0)
	{
		str = (char *)malloc(2);
		if (!str)
			return (NULL);
		str[0] = '0';
		str[1] = '\0';
	}
	else
	{
		str = (char *)malloc(12);
		if (!str)
			return (NULL);
		ft_strlcpy(str, "-2147483648\0", 12);
	}
	return (str);
}

static int	ft_intlen_with_sign(int n)
{
	int	l;

	l = 0;
	if (n < 0)
	{
		n *= -1;
		l++;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 10;
		l++;
	}
	return (l);
}

static char	*ft_reverse(char *str, int len)
{
	int		i;
	char	temp;

	i = 0;
	len -= 1;
	while (i < len)
	{
		temp = str[i];
		str[i] = str[len];
		str[len] = temp;
		i++;
		len--;
	}
	return (str);
}

static void	ft_transform(char *str, int n, int nbr)
{
	int	i;

	i = 0;
	if (n < 0)
		n *= -1;
	while (n > 0)
	{
		str[i++] = (n % 10) + '0';
		n /= 10;
	}
	if (nbr < 0)
		str[i++] = '-';
	str[i] = '\0';
}

char	*ft_itoa(int n)
{
	char	*str;
	int		nbr;
	int		len;

	str = NULL;
	nbr = n;
	len = ft_intlen_with_sign(n);
	if (n == -2147483648 || n == 0)
		return (ft_int_min_and_0_fix(n));
	else if (n != 0)
	{
		str = (char *)malloc(len + 1);
		if (!str)
			return (NULL);
	}
	ft_transform(str, n, nbr);
	ft_reverse(str, len);
	return (str);
}
/*#include <stdio.h>
int    main()
{
	printf("%s\n", ft_itoa(10));
	printf("%s", ft_itoa(-10));
}*/
