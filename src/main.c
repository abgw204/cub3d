/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:17 by gada-sil          #+#    #+#             */
/*   Updated: 2025/11/24 17:15:47 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	set_null(t_game *game)
{
	game->menu_btns[0].img = NULL;
	game->menu_btns[1].img = NULL;
	game->menu_btns[2].img = NULL;
	game->menu_btns[3].img = NULL;
	game->settings[0].img = NULL;
	game->settings[1].img = NULL;
	game->settings[2].img = NULL;
	game->screen.img = NULL;
	game->minimap.img.img = NULL;
}

t_data *get_data(void)
{
	static t_data	data_cub;

	return (&data_cub);
}

//static void	init_vars(t_game *game)
//{
//	game->map = get_data()->map;
//	game->map_w = get_data()->map_w;
//	game->map_h = get_data()->map_h;
//	get_player_info(game);
//	game->minimap.x_bg = (int)game->player.pos.x - 5;
//	game->minimap.y_bg = (int)game->player.pos.y - 5;
//	game->minimap.x_end = (int)game->player.pos.x + 5;
//	game->minimap.y_end = (int)game->player.pos.y + 5;
//	game->minimap.pos.x = 0;
//	game->minimap.pos.y = 0;
//	game->state = MAIN_MENU; // não estará presente no mandatório
//	game->data = get_data();
//	game->keys = ft_calloc(1, 7);
//	game->fps = NULL;
//	ft_memset(game->keys, '0', 7);
//	game->player.speed = 2.0f;
//}

void	init_config(t_config *config)
{
	config->show_fps = 1;
	config->show_mouse = true;
}

int main(int argc, char **argv)
{
	//t_game	game;

	if (argc != 2)
		return (print_error("Usage: ./cub3d <MAP_PATH>"));
	if (parse_given_file(argv[1]))
		return (1);
	fill_in_with_x();
	exit(0);
	//init_vars(&game);
	//init_config(&game.config);
	//set_null(&game);
	//if (init_game(&game))
	//	return (1);
	return (0);
}
