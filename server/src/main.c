/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:02:43 by gada-sil          #+#    #+#             */
/*   Updated: 2025/12/04 15:05:19 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server.h"

void	initialize_players(t_player *players)
{
	int	i;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		players[i].connected = 0;
		players[i].packet_received = false;
	}
}

int find_player(t_player *players, struct sockaddr_in *addr)
{
	int	i;

	i = -1;
    while (++i < MAX_PLAYERS)
    {
        if (players[i].connected &&
            players[i].addr.sin_addr.s_addr == addr->sin_addr.s_addr &&
            players[i].addr.sin_port == addr->sin_port)
            return i;
    }
    return -1;
}

int add_player(t_player *players, struct sockaddr_in *addr, char *buffer)
{
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		if (!players[i].connected)
		{
			memcpy(&players[i].id, buffer + 4, sizeof(int));
			players[i].addr = *addr;
			players[i].connected = 1;
			players[i].x = 5.0;
			players[i].y = 5.0;
			players[i].speed = 20;
			return 0;
		}
	}
	return 1;
}

void update_players_inputs(t_player *p, char *keys)
{
	int	i;

	i = -1;
	while (++i < 4)
		p->keys[i] = keys[i];
}

void	simulate_players(t_player *players, double delta_time)
{
	int	i;

	i = -1;
	while (++i < MAX_PLAYERS)
    {
        if (!players[i].connected)
            continue;
        if (players[i].keys[0] == '1')
            players[i].y -= players[i].speed * delta_time;
        if (players[i].keys[1] == '1')
            players[i].x -= players[i].speed * delta_time;
        if (players[i].keys[2] == '1')
            players[i].y += players[i].speed * delta_time;
        if (players[i].keys[3] == '1')
            players[i].x += players[i].speed * delta_time;
    }
}

void	update_idle_time(t_player *players)
{
	int	i;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		if (players[i].connected)
		{
			if (players[i].packet_received == false)
				players[i].idle_time += g_delta_time;
			else
			{
				players[i].idle_time = 0.0;
				players[i].packet_received = false;
			}
		}
	}
}

void	send_packets(t_server *s, char *buffer_send)
{
	t_player	*players;
	int			i;

	i = -1;
	players = s->players;
	while (++i < MAX_PLAYERS)
		sendto(s->soc.socket, buffer_send, MAX_PLAYERS * SEND_PACKET_SIZE, 0,
			(struct sockaddr *)&players[i].addr, sizeof(players[i].addr));
}

void	broadcast_state(t_server *s)
{
	char	buffer_send[MAX_PLAYERS * SEND_PACKET_SIZE];
	int offset = 0;
	t_player	*player;
	player = s->players;
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		if (player[i].connected)
		{
			printf("x: %f y: %f delta: %f\n", player[i].x, player[i].y, g_delta_time);
			memcpy(buffer_send + offset, &player[i].id, sizeof(int));
			memcpy(buffer_send + offset + 4, &player[i].x, sizeof(double));
			memcpy(buffer_send + offset + 12, &player[i].y, sizeof(double));
			memcpy(buffer_send + offset + 20, &player[i].connected, sizeof(int));
			offset += OFFSET;
		}
		else
		{
			memcpy(buffer_send + offset + 20, &player[i].connected, sizeof(int));
			offset += OFFSET;
		}
	}
	send_packets(s, buffer_send);
}

void	disconnect_down_players(t_player *players)
{
	struct sockaddr_in clean_addr = {0};
	for (int i = 0; i < MAX_PLAYERS; i++)
		if (players[i].connected && players[i].idle_time >= 5.0)
		{
			players[i].connected = 0;
			players[i].id = -1;
			players[i].addr = clean_addr;
		}
}

void	update_state(t_server *s)
{
	update_idle_time(s->players);
	while (acumulator >= tick_time)
	{
		simulate_players(s->players, tick_time);
		acumulator -= tick_time;
	}
	broadcast_state(s);
	disconnect_down_players(s->players);
	usleep(1000);
}

int	server_update(t_server *s)
{
	char	buffer[8];
	int		id;
	int		bytes;

	while (1)
	{
		while (1)
		{
			bytes = recvfrom(s->soc.socket, buffer, sizeof(buffer), 0,
				(struct sockaddr *)&s->soc.peer, &s->soc.peer_len);
			if (bytes <= 0)
				break ;
			id = find_player(s->players, &s->soc.peer);
			if (id == -1)
				add_player(s->players, &s->soc.peer, buffer);
			else
			{
				s->players[id].packet_received = true;
				update_players_inputs(s->players, buffer);
			}
		}
		update_state(s);
	}
	return (0);
}

int	main(void)
{
	t_server	s;

	if (init_socket(&s.soc))
		perror("server");
	initialize_players(s.players);
	if (server_update(&s))
	{
		perror("server");
		return (1);
	}
	return (0);
}
