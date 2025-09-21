#include "../include/cub3d.h"

static void	init_vars(t_game *game)
{
	game->state = MAIN_MENU; // não estará presente no mandatório
	game->mlx = NULL;
	game->win = NULL;
	game->map = NULL;
	game->map_w = 0;
	game->map_h = 0;
	game->keys = ft_calloc(1, 256);
	ft_memset(game->keys, '0', 256);
	game->player.speed = 50.0f;
	t_vector2	p_pos = {0};
	t_vector2	p_dir = {0};
	game->player.pos = p_pos;
	game->player.dir = p_dir;
}

int main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
		return (print_error("Invalid number of parameters!"));
	if (parse_map_file(argv[1]))
		return (1);
	init_vars(&game);
	//if (parsing_and_map_stuff(&game))
	//	return (1);
	if (init_game(&game))
		return (1);
	return (0);
}
