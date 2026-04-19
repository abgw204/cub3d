/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_raylib.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opencode                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19                                #+#    #+#             */
/*   Updated: 2026/04/19                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_rl.h"

#include <stdlib.h>

t_data	*get_data(void)
{
	static t_data	data_cub;

	return (&data_cub);
}

static int	parse_int_or(const char *s, int fallback)
{
	if (s == NULL || *s == '\0')
		return (fallback);
	return (atoi(s));
}

int	main(int argc, char **argv)
{
	const char	*map_path;
	int			my_id;
	const char	*server_ip;
	int			port;
	t_rl_ctx	ctx;

	if (argc != 4 && argc != 5)
		return (print_error("Usage: ./cub3d_rl <MAP_PATH> <ID> <SERVER_IP> [PORT]"));
	map_path = argv[1];
	my_id = atoi(argv[2]);
	server_ip = argv[3];
	port = (argc == 5) ? parse_int_or(argv[4], 5000) : 5000;
	if (port <= 0 || port > 65535)
		return (print_error("Invalid PORT"));
	if (rl_app_init(&ctx, map_path, my_id, server_ip, port))
	{
		rl_app_shutdown(&ctx);
		return (1);
	}
	while (!WindowShouldClose())
		rl_app_tick(&ctx);
	rl_app_shutdown(&ctx);
	return (0);
}
