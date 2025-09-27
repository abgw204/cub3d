/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 13:01:37 by gada-sil          #+#    #+#             */
/*   Updated: 2024/09/23 20:15:06 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_rgb_atoi(const char *str)
{
	int	res;

	res = 0;
	if (!str)
		return (0);
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
	while (*str >= '0' && *str <= '9')
		res = res * 10 + (*str++ - 48);
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
