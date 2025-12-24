/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:02:43 by gada-sil          #+#    #+#             */
/*   Updated: 2025/12/10 15:57:13 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server.h"

/*
	1. Set socket family to ipv4
	2. Make it listen to any local address
	3. Set the port clients will access
	4. Create UDP socket (SOCK_DGRAM) fd with NONBLOCK FLAG
		(recvfrom won't wait for packets, it will only
		read the packets in the network stack and continue)
	5. Assign the address of the server program to socket
	6. Get peer length to use later on recvfrom
*/

int	init_socket(t_socket *soc)
{
	soc->me.sin_family = AF_INET;
	soc->me.sin_addr.s_addr = INADDR_ANY;
	soc->me.sin_port = htons(5000);
	soc->socket = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
	if (soc->socket == -1)
		return (1);
	if (bind(soc->socket, (struct sockaddr *)&soc->me, sizeof(soc->me)) == -1)
	{
		close(soc->socket);
		return (1);
	}
	soc->peer_len = sizeof(soc->peer);
	return (0);
}
