/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:28 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/24 17:05:29 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	print_error_free(t_game *game, char *error_message)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(error_message, 2);
	free(game->map);
	if (game->mlx)
		mlx_destroy_display(game->mlx);
	return (1);
}

int	print_error(char *error_message)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(error_message, 2);
	return (1);
}

int	print_perror(void)
{
	ft_putendl_fd("Error", 2);
	perror("cub3d");
	return (1);
}
