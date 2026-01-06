/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_fc_colors.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:06 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/05 12:09:33 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static char	*join_colors(char **colors)
{
	char	*r;
	char	*g;
	char	*b;
	char	*temp;
	char	*res;

	r = rgb_to_hex(ft_rgb_atoi(colors[1]));
	g = rgb_to_hex(ft_rgb_atoi(colors[2]));
	b = rgb_to_hex(ft_rgb_atoi(colors[3]));
	if (!r || !g || !b)
	{
		free(r);
		free(g);
		free(b);
		return (NULL);
	}
	temp = ft_strjoin(r, g);
	res = ft_strjoin(temp, b);
	free(r);
	free(g);
	free(b);
	free(temp);
	return (res);
}

static int	set_color(char **config)
{
	char	*rgb;

	rgb = join_colors(config);
	if (!rgb)
		return (-1);
	return (hex_str_to_int(rgb, "0123456789ABCDEF"));
}

int	parse_fc_colors(char ***config)
{
	while (*config)
	{
		if (ft_strlen(**config) == 1 && ***config == 'F')
			get_data()->f_color = set_color(*config);
		else if (ft_strlen(**config) == 1 && ***config == 'C')
			get_data()->c_color = set_color(*config);
		config++;
	}
	if (get_data()->f_color == -1)
		return(free_all(NULL, get_data()->config, "Invalid floor color number!"));
	if (get_data()->c_color == -1)
		return(free_all(NULL, get_data()->config, "Invalid ceiling color number!"));
	return (0);
}
