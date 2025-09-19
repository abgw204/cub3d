#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include "libft.h"

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

extern double	delta_time;

typedef struct	Vector2
{
	float	x;
	float	y;
}	t_vector2;

typedef struct	Player
{
	t_vector2	pos;
	t_vector2	dir;
}	t_player;

typedef struct	GameData
{
	char	*map;
	int		map_w;
	int		map_h;
}			t_game;

int		parse_map_file(char *file);
int		print_error(char *error_message);
int		print_perror(void);

#endif
