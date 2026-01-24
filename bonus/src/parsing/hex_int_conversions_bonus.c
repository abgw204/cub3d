/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_int_conversions_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 13:11:46 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/24 15:38:32 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

static int	strchr_index(const char *str, char stop)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != stop)
		i++;
	return (i);
}

int	hex_str_to_int(char *str, char *hex)
{
	int		res;
	int		i;
	int		power;
	int		pos;

	res = 0;
	i = (int)ft_strlen(str) - 1;
	power = 0;
	while (i > -1 && str[i])
	{
		pos = strchr_index(hex, str[i]);
		res += pos * pow(16, power++);
		i--;
	}
	free(str);
	return (res);
}

char	*rgb_to_hex(int rgb)
{
	char	*hex;
	char	*res;
	char	*temp;
	int		i;

	if (rgb == 0)
		return (ft_strdup("00"));
	if (rgb == -1)
		return (NULL);
	i = 1;
	temp = (char *)ft_calloc(3, 1);
	hex = ft_strdup("0123456789ABCDEF");
	if (rgb < 16)
		temp[0] = '0';
	while (rgb > 0)
	{
		temp[i--] = hex[rgb % 16];
		rgb /= 16;
	}
	if (i == -1)
		i++;
	res = ft_strdup(temp + i);
	free(temp);
	free(hex);
	return (res);
}
