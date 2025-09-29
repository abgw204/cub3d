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

/* SCREEN SIZE */
# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080

/* KEYS */
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

/* GAME STATES */
# define MAIN_MENU 0
# define IN_GAME 1
# define IN_SETTINGS 2

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
	int		x;
	int		y;
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

typedef struct	Config
{
	int		show_fps;
}	t_config;

typedef struct	GameData
{
	void		*win;
	void		*mlx;
	char		*map;
	int			map_w;
	int			map_h;
	int			state;
	t_config	game_config;
	t_image		menu_btns[4];
	t_image		settings[3];
	t_data		*data;
	t_player	player;
	char		*keys;
}			t_game;

/* TIME */
void	set_delta_time(t_game *game);
double	get_time_in_seconds(void);
void	limit_fps(double target_fps);

/* FILE PARSING */
int		parse_given_file(char *file);
int		parse_file(int map_fd, char **config, char **symbols, int i);
int		parse_fc_colors(char ***config);
char	*rgb_to_hex(int rgb);
int		hex_str_to_int(char *str, char *hex);
int		compare_symbols(char *str, char **symbols);
int		free_all(char **textures_matrix, char ***textures_array,
		char *error_msg);
void	free_stack_matrix_array(char ***arr);
void	initialize_matrix(char **matrix, int size);

/* MOUSE */
int		mouse_move(int x, int y, void *param);
int		mouse_move_menu(t_game *game, int x, int y);
int		mouse_input(int mouse_btn, int x, int y, void *param);

/* MENU */
int		configure_menu_images(t_game *game);
int		load_menu_images(t_game *game);
int		show_main_menu(t_game *game);
int		check_btn_collision(t_image *img, int x, int y);
void	set_buttons_pos(t_image *menu_btns);
void	set_menu_images_info(t_image *images);

/* SETTINGS */
int		show_settings(t_game *game);

/* DRAW */
void	revert_colors(t_image *image, unsigned int color1, unsigned int color2);
void	draw_circle(t_vector2 pos, int radius, int color, t_image *image);
void	draw_pixel_in_image(t_image *image, int x, int y, int color);

/* ERROR */
int		print_error(char *error_message);
int		print_error_free(t_game *game, char *error_message);
int		print_perror(void);

/* GAME */
int		init_game(t_game *game);
t_data	*get_data(void);

#endif
