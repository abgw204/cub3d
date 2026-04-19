/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_platform.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opencode                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19                                #+#    #+#             */
/*   Updated: 2026/04/19                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/rl_platform.h"

#ifndef _WIN32

# include <unistd.h>
# include <fcntl.h>

int	rl_platform_net_startup(void)
{
	return (0);
}

void	rl_platform_net_cleanup(void)
{
}

int	rl_platform_socket_set_nonblocking(cub3d_socket_t s)
{
	int	flags;

	flags = fcntl(s, F_GETFL, 0);
	if (flags == -1)
		return (-1);
	if (fcntl(s, F_SETFL, flags | O_NONBLOCK) == -1)
		return (-1);
	return (0);
}

void	rl_platform_socket_close(cub3d_socket_t s)
{
	close(s);
}

#else

int	rl_platform_net_startup(void)
{
	WSADATA	wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return (-1);
	return (0);
}

void	rl_platform_net_cleanup(void)
{
	WSACleanup();
}

int	rl_platform_socket_set_nonblocking(cub3d_socket_t s)
{
	u_long	mode;

	mode = 1;
	if (ioctlsocket(s, FIONBIO, &mode) != 0)
		return (-1);
	return (0);
}

void	rl_platform_socket_close(cub3d_socket_t s)
{
	closesocket(s);
}

#endif
