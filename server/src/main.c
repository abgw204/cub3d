/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:02:43 by gada-sil          #+#    #+#             */
/*   Updated: 2025/12/19 16:38:20 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/server.h"

void	initialize_players(t_s_player *players)
{
	int	i;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		players[i].connected = 0;
		players[i].packet_received = false;
		players[i].id = -1;
	}
}

int find_player(t_s_player *players, struct sockaddr_in *addr)
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

int add_player(t_s_player *players, struct sockaddr_in *addr, char *buffer, t_server *s)
{
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		if (!players[i].connected)
		{
			memcpy(&players[i].id, buffer + 4, sizeof(int));
			memcpy(&players[i].angle, buffer + 8, sizeof(double));
			printf("ID: %d\n", players[i].id);
			players[i].addr = *addr;
			players[i].dx = cos(players[i].angle);
			players[i].dy = sin(players[i].angle);
			players[i].plane_x = -players[i].dy * FOV;
			players[i].plane_y =  players[i].dx * FOV;
			if (s->valid_spawn_counter == 0)
				return 1;
			int r = rand() % s->valid_spawn_counter;
			players[i].x = (double)(s->pos[r].x + 0.5);
			players[i].y = (double)(s->pos[r].y + 0.5);
			printf("x: %.3f\n", players[i].x);
			printf("y: %.3f\n", players[i].y);
			players[i].connected = 1;
			players[i].packet_received = true;
			players[i].idle_time = 0.0;
			players[i].speed = 30.0;
			return 0;
		}
	}
	return 1;
}

void update_player_inputs(t_s_player *p, char *buffer)
{
	int	i;

	i = -1;
	p->packet_received = true;
	while (++i < 4)
		p->keys[i] = buffer[i];
	memcpy(&p->angle, buffer + 8, sizeof(double));
	p->dx = cos(p->angle);
	p->dy = sin(p->angle);
	p->plane_x = -p->dy * FOV;
	p->plane_y =  p->dx * FOV;
}

void	move_w(t_s_player *player, t_server *s)
{
	double	new_x;
	double	new_y;
	double	coll_x;
	double	coll_y;

	if (player->dx > 0.0)
		coll_x = COLLISION_DIST_S;
	else
		coll_x = -COLLISION_DIST_S;
	if (player->dy > 0.0)
		coll_y = COLLISION_DIST_S;
	else
		coll_y = -COLLISION_DIST_S;
	new_x = player->x + player->dx * player->speed * g_s_delta_time;
	new_y = player->y + player->dy * player->speed * g_s_delta_time;
    if (s->map[(int)player->y * s->map_w + (int)(new_x + coll_x)] != '1')
		player->x = new_x;
	if (s->map[(int)(new_y + coll_y) * s->map_w + (int)player->x] != '1')
		player->y = new_y;
}

void	move_a(t_s_player *player, t_server *s)
{
	t_double_vector2	side;
	double	new_x;
	double	new_y;
	double	coll_x;
	double	coll_y;

	if (-player->plane_x > 0.0)
		coll_x = COLLISION_DIST_S;
	else
		coll_x = -COLLISION_DIST_S;
	if (-player->plane_y > 0.0)
		coll_y = COLLISION_DIST_S;
	else
		coll_y = -COLLISION_DIST_S;
    side.x = player->dy;
	side.y = -player->dx;
    new_x = player->x + side.x * player->speed * g_s_delta_time;
    new_y = player->y + side.y * player->speed * g_s_delta_time;
	if (s->map[(int)player->y * s->map_w + (int)(new_x + coll_x)] != '1')
		player->x = new_x;
	if (s->map[(int)(new_y + coll_y) * s->map_w + (int)player->x] != '1')
		player->y = new_y;
}

void	move_s(t_s_player *player, t_server *s)
{
	double	new_x;
	double	new_y;
	double	coll_x;
	double	coll_y;

	if (player->dx > 0.0)
		coll_x = -COLLISION_DIST_S;
	else
		coll_x = COLLISION_DIST_S;
	if (player->dy > 0.0)
		coll_y = -COLLISION_DIST_S;
	else
		coll_y = COLLISION_DIST_S;
	new_x = player->x + -player->dx * player->speed * g_s_delta_time;
	new_y = player->y + -player->dy * player->speed * g_s_delta_time;
    if (s->map[(int)player->y * s->map_w + (int)(new_x + coll_x)] != '1')
		player->x = new_x;
	if (s->map[(int)(new_y + coll_y) * s->map_w + (int)player->x] != '1')
		player->y = new_y;
}

void	move_d(t_s_player *player, t_server *s)
{
    t_double_vector2	side;
	double	new_x;
	double	new_y;
	double	coll_x;
	double	coll_y;

	if (player->plane_x > 0.0)
		coll_x = COLLISION_DIST_S;
	else
		coll_x = -COLLISION_DIST_S;
	if (player->plane_y > 0.0)
		coll_y = COLLISION_DIST_S;
	else
		coll_y = -COLLISION_DIST_S;
    side.x = -player->dy;
	side.y = player->dx;
    new_x = player->x + side.x * player->speed * g_s_delta_time;
    new_y = player->y + side.y * player->speed * g_s_delta_time;
	if (s->map[(int)player->y * s->map_w + (int)(new_x + coll_x)] != '1')
		player->x = new_x;
	if (s->map[(int)(new_y + coll_y) * s->map_w + (int)player->x] != '1')
		player->y = new_y;
}

void	simulate_players(t_server *s)
{
	t_s_player	*players;
	int			i;

	players = s->players;
	i = -1;
	while (++i < MAX_PLAYERS)
    {
        if (!players[i].connected)
            continue;
        if (players[i].keys[0] == '1')
            move_w(&players[i], s);
        if (players[i].keys[1] == '1')
            move_a(&players[i], s);
        if (players[i].keys[2] == '1')
            move_s(&players[i], s);
        if (players[i].keys[3] == '1')
            move_d(&players[i], s);
    }
}

void	update_idle_time(t_s_player *players)
{
	int	i;

	i = -1;
	while (++i < MAX_PLAYERS)
	{
		if (players[i].connected)
		{
			if (players[i].packet_received == false)
				players[i].idle_time += g_s_delta_time;
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
	t_s_player	*players;
	int			i;

	i = -1;
	players = s->players;
	while (++i < MAX_PLAYERS)
		sendto(s->soc.socket, buffer_send, MAX_PLAYERS * SEND_PACKET_SIZE, 0,
			(struct sockaddr *)&players[i].addr, sizeof(players[i].addr));
}

void	broadcast_state(t_server *s)
{
	t_s_player	*player;
	char		buffer_send[MAX_PLAYERS * SEND_PACKET_SIZE];
	int			offset;

	player = s->players;
	offset = 0;
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		/*printf("id: %d\n", player[i].id);
		printf("connected: %d\n", player[i].connected);
		printf("plane_x: %f\n", player[i].plane_x);*/
		if (player[i].connected)
		{
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

void	disconnect_down_players(t_s_player *players)
{
	struct sockaddr_in	clean_addr;
	int					i;

	memset(&clean_addr, 0, sizeof(struct sockaddr_in));
	i = -1;
	while (++i < MAX_PLAYERS)
	{
		if (players[i].connected && players[i].idle_time >= 0.1)
		{
			players[i].connected = 0;
			players[i].id = -1;
			players[i].addr = clean_addr;
			players[i].packet_received = false;
			players[i].idle_time = 0.0;
		}
	}
}

void	update_state(t_server *s)
{
	update_idle_time(s->players);
	while (acumulator >= tick_time)
	{
		simulate_players(s);
		acumulator -= tick_time;
	}
	broadcast_state(s);
	disconnect_down_players(s->players);
	usleep(400);
}

int	server_update(t_server *s)
{
	char	buffer[16];
	int		idx;
	int		bytes;

	while (1)
	{
		set_server_delta_time();
		acumulator += g_s_delta_time;
		while (1)
		{
			bytes = recvfrom(s->soc.socket, buffer, sizeof(buffer), 0,
				(struct sockaddr *)&s->soc.peer, &s->soc.peer_len);
			if (bytes <= 0)
				break ;
			idx = find_player(s->players, &s->soc.peer);
			if (idx == -1)
				add_player(s->players, &s->soc.peer, buffer, s);
			else
				update_player_inputs(&s->players[idx], buffer);
		}
		update_state(s);
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_server	s;

	srand(time(NULL));
	
	if (ac != 2)
	{
		ft_putendl_fd("Usage: ./cub3d_server <MAP_PATH>", 2);
		return (1);
	}
	if (init_socket(&s.soc))
	perror("server");
	initialize_players(s.players);
	s.map_w = 0;
	if (parse_map_s(&s, av[1]))
	{
		close(s.soc.socket);
		return (1);
	}
	s.valid_spawn_counter = 0;
	s.pos = malloc(sizeof(t_pos) * s.map_h * s.map_w);
	for (int y = 0; y < s.map_h; y++)
	{
		for (int x = 0; x < s.map_w; x++)
		{
			if (s.map[y * s.map_w + x] == '0')
			{
				s.pos[s.valid_spawn_counter].x = x;
				s.pos[s.valid_spawn_counter].y = y;
				s.valid_spawn_counter++;
			}
		}
	}
	if (server_update(&s))
	{
		perror("server");
		return (1);
	}
	return (0);
}
