/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_net.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opencode                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19                                #+#    #+#             */
/*   Updated: 2026/04/19                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_rl.h"

// Compile-time checks for our wire structs.
typedef char	t_assert_input_size[(sizeof(t_net_input) == 17) ? 1 : -1];
typedef char	t_assert_state_size[(sizeof(t_net_state) == 28) ? 1 : -1];

static void	net_input_to_bytes(const t_net_input *in, char out[17])
{
	memcpy(out + 0, in->keys, 4);
	memcpy(out + 4, &in->id, sizeof(int));
	memcpy(out + 8, &in->angle, sizeof(double));
	memcpy(out + 16, &in->event, 1);
}

static void	net_state_from_bytes(t_net_state *st, const char *buf)
{
	memcpy(&st->id, buf + 0, sizeof(int));
	memcpy(&st->x, buf + 4, sizeof(double));
	memcpy(&st->y, buf + 12, sizeof(double));
	memcpy(&st->connected, buf + 20, sizeof(int));
	memcpy(&st->health, buf + 24, sizeof(int));
}

int	rl_net_init(t_game *game, int my_id, const char *server_ip, int port)
{
	if (rl_platform_net_startup() != 0)
		return (print_error("Winsock init failed"));
	game->soc.socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (game->soc.socket == CUB3D_INVALID_SOCKET)
		return (print_perror());
	if (rl_platform_socket_set_nonblocking(game->soc.socket) != 0)
		return (print_perror());
	memset(&game->soc.peer, 0, sizeof(game->soc.peer));
	game->soc.peer.sin_family = AF_INET;
	game->soc.peer.sin_port = htons((uint16_t)port);
	if (inet_pton(AF_INET, server_ip, &game->soc.peer.sin_addr) != 1)
		return (print_error("Invalid server IP"));
	game->soc.peer_len = sizeof(game->soc.peer);
	game->my_id = my_id;
	return (0);
}

void	rl_net_send_inputs(t_game *game)
{
	t_net_input	in;
	char		buf[17];

	memcpy(in.keys, game->keys, 4);
	in.id = game->my_id;
	memcpy(&in.angle, game->keys + 8, sizeof(double));
	in.event = game->keys[16];
	net_input_to_bytes(&in, buf);
	(void)sendto(game->soc.socket, buf, sizeof(buf), 0,
		(struct sockaddr *)&game->soc.peer, sizeof(game->soc.peer));
}

void	rl_net_receive_state(t_game *game)
{
	char			tmp_buf[MAX_PLAYERS * SEND_PACKET_SIZE];
	char			latest_buf[MAX_PLAYERS * SEND_PACKET_SIZE];
	int			bytes;
	int			latest_bytes;
	int			offset;
	int			i;
	t_net_state	st;

	bytes = 1;
	latest_bytes = 0;
	while (bytes > 0)
	{
		bytes = recvfrom(game->soc.socket, tmp_buf, sizeof(tmp_buf), 0,
			(struct sockaddr *)&game->soc.peer, &game->soc.peer_len);
		if (bytes > 0 && bytes <= (int)sizeof(tmp_buf))
		{
			memcpy(latest_buf, tmp_buf, bytes);
			latest_bytes = bytes;
		}
	}
	if (latest_bytes <= 0)
		return;
	offset = 0;
	for (i = 0; i < MAX_PLAYERS; i++)
	{
		if (offset + SEND_PACKET_SIZE > latest_bytes)
			break;
		net_state_from_bytes(&st, latest_buf + offset);
		if (!st.connected)
		{
			game->players[i].connected = 0;
			game->players[i].id = -1;
			game->players[i].health = 0;
			offset += SEND_PACKET_SIZE;
			continue;
		}
		game->players[i].connected = st.connected;
		game->players[i].id = st.id;
		game->players[i].x = st.x;
		game->players[i].y = st.y;
		game->players[i].health = st.health;
		if (st.id == game->my_id)
		{
			game->player.pos.x = st.x;
			game->player.pos.y = st.y;
			game->health = st.health;
		}
		offset += SEND_PACKET_SIZE;
	}
}
