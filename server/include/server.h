/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:03:25 by gada-sil          #+#    #+#             */
/*   Updated: 2025/12/10 12:07:26 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <arpa/inet.h>
# include <sys/socket.h>
# include <sys/time.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include "../../include/libft.h"

# define MAX_PLAYERS 4
# define INPUT_SIZE 4
# define ANGLE_SIZE 8
# define ID_SIZE 4
# define SEND_PACKET_SIZE 24
# define OFFSET SEND_PACKET_SIZE

# define FOV 0.75
# define COLLISION_DIST_S 0.3

extern double			g_s_delta_time;
extern double			acumulator;
extern const double		tick_time;

typedef struct	s_socket
{
	int					socket;
	struct sockaddr_in	peer;
	struct sockaddr_in	me;
	socklen_t			peer_len;
}	t_socket;

typedef struct	s_s_player
{
    struct sockaddr_in	addr;
    double				x;
	double				y;
	double				dx;
	double				dy;
	double				plane_x;
	double				plane_y;
	double				angle;
    double				speed;
    int					connected;
	int					id;
	char				keys[4];
	bool				packet_received;
	double				idle_time;
}	t_s_player;

typedef struct	s_dv2
{
	double	x;
	double	y;
}	t_double_vector2;

typedef struct	s_server
{
	t_socket	soc;
	t_s_player	players[MAX_PLAYERS];
	t_list		*map_list;
	int			map_w;
	int			map_h;
	char		*map;
}	t_server;

int		init_socket(t_socket *soc);
void	set_server_delta_time(void);
int		parse_map_s(t_server *s, char *file);
int		check_valid(char *line, char *valids);
int		error(char *line, t_list *list, char *error_message);
char	*jump_blank_lines(int *file_fd);
int		search_bigger(char *line, int *w);
void	trim_newlines_map(t_list *map);

#endif
