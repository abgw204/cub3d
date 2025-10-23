/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:17 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/29 19:05:03 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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
	get_player_info(game);
	game->minimap.x_bg = (int)game->player.pos.x - 5;
	game->minimap.y_bg = (int)game->player.pos.y - 5;
	game->minimap.x_end = (int)game->player.pos.x + 5;
	game->minimap.y_end = (int)game->player.pos.y + 5;
	game->minimap.pos.x = 0;
	game->minimap.pos.y = 0;
	game->state = MAIN_MENU; // não estará presente no mandatório
	game->data = get_data();
	game->keys = ft_calloc(1, 256);
	ft_memset(game->keys, '0', 256);
	game->player.speed = 60.0f;
}

void	init_config(t_config *config)
{
	config->show_fps = 0;
}

int main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (print_error("Usage: ./cub3d <MAP_PATH>"));
	if (parse_given_file(argv[1]))
		return (1);
	init_vars(&game);
	init_config(&game.config);
	if (init_game(&game))
		return (1);
	return (0);
}
