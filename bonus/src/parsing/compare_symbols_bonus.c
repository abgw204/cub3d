/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_symbols_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:00:22 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/24 15:38:08 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_bonus.h"

int	compare_symbols(char *str, char **symbols)
{
	int	i;

	i = 0;
	while (symbols[i])
	{
		if (!ft_strcmp(symbols[i], str))
		{
			free(symbols[i]);
			symbols[i] = ft_strdup("");
			return (1);
		}
		i++;
	}
	return (0);
}
