/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:17 by gada-sil          #+#    #+#             */
/*   Updated: 2025/12/19 12:59:22 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_null(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
		game->menu_btns[i++].img = NULL;
	i = 0;
	while (i < 3)
		game->settings[i++].img = NULL;
	i = 0;
	game->gun.img = NULL;
	game->win = NULL;
	game->fps = NULL;
	game->screen.img = NULL;
	game->minimap.img.img = NULL;
	game->n.img = NULL;
	game->s.img = NULL;
	game->w.img = NULL;
	game->e.img = NULL;
	game->enemy.img = NULL;
}

t_data *get_data(void)
{
	static t_data	data_cub;

	return (&data_cub);
}

static void	init_vars(t_game *game)
{
	game->map = get_data()->map;
	game->map_w = get_data()->map_w;
	game->map_h = get_data()->map_h;
	game->m_x = 0;
	game->m_y = 0;
	get_player_info(game);
	game->minimap.x_bg = (int)game->player.pos.x - 5;
	game->minimap.y_bg = (int)game->player.pos.y - 5;
	game->minimap.x_end = (int)game->player.pos.x + 5;
	game->minimap.y_end = (int)game->player.pos.y + 5;
	game->minimap.pos.x = 0;
	game->minimap.pos.y = 0;
	game->state = MAIN_MENU; // não estará presente no mandatório
	game->data = get_data();
	game->keys = ft_calloc(1, 17);
	game->local_keys = ft_calloc(1, 3);
	game->is_shooting = false;
	ft_memset(game->keys, '0', 4);
	ft_memset(game->keys + 17, '0', 1);
	ft_memset(game->local_keys, '0', 3);
	game->player.speed = 2.0f;
}

void	init_config(t_config *config)
{
	config->show_fps = 0;
	config->show_mouse = true;
}

int main(int argc, char **argv)
{
	t_game	game;

	if (argc != 3)
		return (print_error("Usage: ./cub3d <MAP_PATH> <ID>"));
	if (parse_given_file(argv[1]))
		return (1);
	init_vars(&game);
	init_config(&game.config);
	set_null(&game);
	game.soc.socket = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);

    memset(&game.soc.peer, 0, sizeof(game.soc.peer));
	game.my_id = atoi(argv[2]);
	memcpy(game.keys + 4, &game.my_id, sizeof(int));
    memset(&game.soc.peer, 0, sizeof(game.soc.peer));
	game.soc.peer.sin_family = AF_INET;
	game.soc.peer.sin_port = htons(9800);
    inet_pton(AF_INET, "127.0.0.1", &game.soc.peer.sin_addr);

	int i = -1;
	while (++i < MAX_PLAYERS)
		game.players[i].connected = 0;
	if (init_game(&game))
		return (1);
	return (0);
}
