/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 18:02:43 by gada-sil          #+#    #+#             */
/*   Updated: 2025/11/25 18:05:16 by gada-sil         ###   ########.fr       */
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

int	server_update(t_server *s)
{
	//int	bytes;

	(void)s;
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
