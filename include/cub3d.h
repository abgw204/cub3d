/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:13 by gada-sil          #+#    #+#             */
/*   Updated: 2025/11/05 02:23:21 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdint.h>
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <sys/time.h>
# include "../lib/minilibx-linux/mlx.h"
# include "libft.h"

/* SCREEN SIZE */
# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 768

/* KEYS */
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363

/* GAME STATES */
# define MAIN_MENU 0
# define IN_GAME 1
# define IN_SETTINGS 2

/* COLORS */
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define WHITE_ISH 0xFFFFFE

/* MATH */
# define PI 3.14159265358979323846

extern double	g_delta_time;

typedef struct Data
{
	char	**config[7];
	t_list	*map_list;
	char	*map;
	int		map_w;
	int		map_h;
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

typedef struct	UIntVector2
{
	unsigned int	x;
	unsigned int	y;
}	t_uiv2;

typedef struct	IntVector2
{
	int	x;
	int	y;
}	t_iv2;

typedef struct	FloatVector2
{
	float	x;
	float	y;
}	t_fv2;

typedef struct	DoubleVector2
{
	double	x;
	double	y;
}	t_dv2;

typedef struct	Player
{
	t_dv2	pos;
	t_dv2	dir;
	t_dv2	plane;
	double	angle;
	double	speed;
}	t_player;

typedef struct	Config
{
	int	show_fps;
}	t_config;

typedef struct	Minimap
{
	int		x_bg;
	int		y_bg;
	int		x_end;
	int		y_end;
	t_iv2	pos;
	t_image	img;
}	t_minimap;

typedef struct	GameData
{
	void		*win;
	void		*mlx;
	char		*map;
	int			map_w;
	int			map_h;
	int			state;
	t_config	config;
	t_image		menu_btns[4];
	t_image		settings[3];
	t_minimap	minimap;
	t_image		screen;
	t_data		*data;
	t_player	player;
	char		*fps;
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
int 	parse_map(int file_fd);
char	*rgb_to_hex(int rgb);
int		hex_str_to_int(char *str, char *hex);
int		compare_symbols(char *str, char **symbols);
int		free_all(char **textures_matrix, char ***textures_array,
		char *error_msg);
void	free_stack_matrix_array(char ***arr);
void	initialize_matrix(char **matrix, int size);
void	trim_newline_chars(char ***config);
void	trim_newlines_map(t_list *map);
int		search_bigger(char *line, int *w);
char	*jump_blank_lines(int *file_fd);
int		error(char *line, t_list *list, char *error_message);
int		check_valid(char *line, char *valids);
void	get_player_info(t_game *game);
int		close_fd(int fd);

/* KEYBOARD*/
int	key_press(int key, void *param);
int key_release(int key, void *param);

/* MOUSE */
int		mouse_move(int x, int y, void *param);
int		mouse_move_menu(t_game *game, int x, int y);
int		mouse_input(int mouse_btn, int x, int y, void *param);

/* MENU */
int		configure_menu_images(t_game *game);
int		load_menu_images(t_game *game);
int		configure_screen_image(t_game *game);
int		show_main_menu(t_game *game);
int		check_btn_collision(t_image *img, int x, int y);
void	set_buttons_pos(t_image *menu_btns);
void	set_menu_images_info(t_image *images);
int		mouse_input_menu(t_game *game, int x, int y, int mouse_btn);

/* MINIMAP */
int		load_minimap(t_game *game);
void	draw_minimap(t_game *game);

/* SETTINGS */
int		show_settings(t_game *game);
int		load_settings_images(t_game *game);
void	set_settings_images_info(t_image *images);
int		configure_settings_images(t_game *game);
int		mouse_move_settings(t_game *game, int x, int y);
int		mouse_input_in_settings(t_game *game, int x, int y, int mouse_btn);

/* DRAW */
void	revert_colors(t_image *image, unsigned int color1, unsigned int color2);
void	draw_circle(t_uiv2 pos, int radius, int color, t_image *image);
void	draw_pixel_in_image(t_image *image, int x, int y, int color);
void	draw_square(t_game *game, t_uiv2 pos, int size, int color);
void    raycast(t_game *game);

/* ERROR */
int		print_error(char *error_message);
int		print_error_free(t_game *game, char *error_message);
int		print_perror(void);

/* GAME */
int		init_game(t_game *game);
void    move_player(t_game *game);
t_data	*get_data(void);
void	free_and_exit(t_game *game);
void	free_images(t_game *game);
int		game_loop(t_game *game);
void    rotate_camera(t_game *game);

#endif
