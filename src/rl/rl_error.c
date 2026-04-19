/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opencode                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19                                #+#    #+#             */
/*   Updated: 2026/04/19                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

#ifdef _WIN32
# include "../../include/cub3d_platform.h"
#endif

int	print_error(char *error_message)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(error_message, 2);
	return (1);
}

int	print_perror(void)
{
	ft_putendl_fd("Error", 2);
	#ifdef _WIN32
	{
		int	err;

		err = WSAGetLastError();
		if (err != 0)
			ft_putendl_fd("cub3d: winsock error", 2);
		else
			perror("cub3d");
	}
	#else
	perror("cub3d");
	#endif
	return (1);
}
