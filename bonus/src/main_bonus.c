/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:17 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/07 16:39:18 by vfidelis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	set_null(t_game *game)
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
	game->door.img = NULL;
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
	game->doors = get_data()->doors;
	game->doors_n = get_data()->doors_n;
	game->m_x = 0;
	game->m_y = 0;
	get_player_info(game);
	game->minimap.x_bg = (int)game->player.pos.x - 5;
	game->minimap.y_bg = (int)game->player.pos.y - 5;
	game->minimap.x_end = (int)game->player.pos.x + 5;
	game->minimap.y_end = (int)game->player.pos.y + 5;
	game->minimap.pos.x = 0;
	game->minimap.pos.y = 0;
	game->state = MAIN_MENU;
	game->data = get_data();
	game->keys = ft_calloc(1, 8);
	game->is_shooting = false;
	game->shoot_timer = 1.0;
	ft_memset(game->keys, '0', 8);
	game->player.speed = 3.0f;
}

void	init_config(t_config *config)
{
	config->show_fps = 0;
	config->show_mouse = true;
}

int main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (print_error("Usage: ./cub3d <MAP_PATH>"));
	if (parse_given_file(argv[1]))
		return (1);
	init_vars(&game);
	char **map = fill_in_with_x();
	int j = 0;
	ft_flood_fill(map, 2, 2, &j);
	init_config(&game.config);
	set_null(&game);
	for (size_t i = 0;  map[i]; i++)
	{
		printf("%s", map[i]);
		printf("\n");
	}
	printf("\n%d\n", j);
	/*if (init_game(&game))
		return (1);
	*/
	return (0);
}
