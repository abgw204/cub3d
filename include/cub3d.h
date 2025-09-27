/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:13 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/24 17:56:19 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <sys/time.h>
# include "../lib/minilibx-linux/mlx.h"
# include "libft.h"

# define WIDTH 1920
# define HEIGHT 1080

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define MAIN_MENU 0
# define IN_GAME 1

extern double	g_delta_time;

typedef struct Data
{
	char	**config[7];
	char	**map_matrix;
	int		f_color;
	int		c_color;
}	t_data;

typedef struct	Image
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		width;
	int		height;
}	t_image;

typedef struct	Vector2
{
	float	x;
	float	y;
}	t_vector2;

typedef struct	Player
{
	t_vector2	pos;
	t_vector2	dir;
	float		speed;
}	t_player;

typedef struct	GameData
{
	t_image		img;
	void		*win;
	void		*mlx;
	char		*map;
	int			map_w;
	int			map_h;
	int			state;
	int			f_color;
	int			c_color;
	t_player	player;
	char		*keys;
}			t_game;

int		parse_given_file(char *file);
int		parse_file(int map_fd, char **config, char **symbols, int i);
int		parse_fc_colors(char ***config);
char	*rgb_to_hex(int rgb);
int		hex_str_to_int(char *str, char *hex);
int		compare_symbols(char *str, char **symbols);
int		free_all(char **textures_matrix, char ***textures_array, char *error_msg);
void	free_stack_matrix_array(char ***arr);
void	initialize_matrix(char **matrix, int size);
void	draw_circle(t_vector2 pos, int radius, int color, t_image *image);
void	draw_pixel_in_image(t_image *image, int x, int y, int color);
int		print_error(char *error_message);
int		print_error_free(t_game *game, char *error_message);
int		print_perror(void);
int		init_game(t_game *game);
int		main_menu_inputs(int mouse_btn, int x, int y, void *param);
int		render_main_menu(t_game *game);
void	set_delta_time(void);
t_data	*get_data(void);

#endif
