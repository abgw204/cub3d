/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:03:25 by gada-sil          #+#    #+#             */
/*   Updated: 2025/11/25 18:45:22 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

#include <stdbool.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <fcntl.h>

typedef struct s_socket
{
	int					socket;
	struct sockaddr_in	peer;
	struct sockaddr_in	me;
}	t_socket;

typedef struct	s_player {
    struct sockaddr_in	addr; // endereço do cliente (para enviar pacotes de volta)
    double				x;
	double				y;
    double				speed;
    int					connected;
	int					id;
	char				keys[4];
	bool				packet_received;
	double				idle_time;
} t_player;

typedef struct s_packet
{
	int		connected;
	double	x;
	double	y;
	int		id;
}	t_packet;



#endif
