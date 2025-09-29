/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:01:37 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/29 19:00:01 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

int	ft_rgb_atoi(const char *str)
{
	int	res;

	res = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (!(*str >= '0' && *str <= '9'))
	{
		if (*str == '-')
			return (-1);
		else if (*str != '+')
			return (0);
		str++;
	}
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != '\n')
			return (-1);
		else if (*str != '\n')
			res = res * 10 + (*str - 48);
		str++;
	}
	if (res > 255)
		return (-1);
	return (res);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	if (!str)
		return (0);
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (!(*str >= '0' && *str <= '9'))
	{
		if (*str == '-')
			sign = -1;
		else if (*str != '+')
			return (0);
		str++;
	}
	while (*str >= '0' && *str <= '9')
		res = res * 10 + (*str++ - 48);
	return (res * sign);
}
/*#include <stdio.h>
#include <stdlib.h>
int main()
{
	printf("%d\n", ft_atoi("\e76"));
	printf("%d", atoi("\e76"));
}*/
