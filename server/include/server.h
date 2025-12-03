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

# include <stdio.h>
# include <unistd.h>
# include <stdbool.h>
# include <string.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <sys/time.h>
# include <errno.h>
# include <fcntl.h>

# define MAX_PLAYERS 4
# define INPUT_SIZE 4
# define ANGLE_SIZE 8
# define ID_SIZE 4
# define SEND_PACKET_SIZE 32

extern double			g_delta_time;
extern double			acumulator;
extern const double		tick_time;

typedef struct	s_socket
{
	int					socket;
	struct sockaddr_in	peer;
	struct sockaddr_in	me;
	socklen_t			peer_len;
}	t_socket;

typedef struct	s_player
{
    struct sockaddr_in	addr;
    double				x;
	double				y;
	double				angle;
    double				speed;
    int					connected;
	int					id;
	char				keys[4];
	bool				packet_received;
	double				idle_time;
}	t_player;

typedef struct	s_server
{
	t_socket	soc;
	t_player	players[MAX_PLAYERS];
}	t_server;

int		init_socket(t_socket *soc);
void	set_delta_time(void);

#endif
