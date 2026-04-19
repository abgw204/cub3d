/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opencode                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19                                #+#    #+#             */
/*   Updated: 2026/04/19                                ###   ########.fr       */
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
# include <stdbool.h>

# include "cub3d_platform.h"
# include "libft.h"

# define SCREEN_WIDTH 1920
# define SCREEN_HEIGHT 1080
# define CONFIG_TOKENS 6

/* COLORS */
# define WHITE_ISH 0xFFFFFE

/* MATH */
# define PI 3.14159265358979323846
# ifndef FOV
#  define FOV 0.75
# endif

/* NETWORKING */
# define MAX_PLAYERS 4
# define SHOOT_DELAY 0.3
# define COLLISION_DIST 0.3
# define SEND_PACKET_SIZE 28

extern double	g_delta_time;

typedef struct s_data		t_data;
typedef struct s_game_data	t_game;

typedef struct s_socket
{
	cub3d_socket_t			socket;
	struct sockaddr_in	peer;
	cub3d_socklen_t		peer_len;
}	t_socket;

typedef struct s_int_vector
{
	int	x;
	int	y;
}	t_iv2;

typedef struct s_double_vector
{
	double	x;
	double	y;
}	t_dv2;

typedef struct s_player
{
	t_dv2	pos;
	t_dv2	dir;
	t_dv2	plane;
	double	angle;
	double	speed;
}	t_player;

typedef struct s_config
{
	bool	show_fps;
	bool	show_mouse;
}	t_config;

typedef struct s_sprite
{
	double			x;
	double			y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	int				screen_x;
	int				width;
	int				height;
	int				start_x;
	int				end_x;
	int				start_y;
	int				end_y;
}	t_sprite;

typedef struct s_players
{
	int			id;
	double		x;
	double		y;
	int			connected;
	int			health;
	t_sprite	sp;
}	t_players;

typedef struct s_game_data
{
	char		*map;
	int			map_w;
	int			map_h;
	char		*fps;
	char		*keys;
	char		*local_keys;
	double		*z_buffer;
	int			screen_w;
	int			screen_h;
	int			my_id;
	bool		is_shooting;
	double		shoot_timer;
	int			health;
	t_player	player;
	t_config	config;
	t_data		*data;

	t_players	players[MAX_PLAYERS];
	t_socket	soc;
	double		server_down_timer;
	bool		packet_received;
}	t_game;

typedef struct s_data
{
	char	**config[7];
	t_list	*map_list;
	char	*map;
	int		map_w;
	int		map_h;
	int		f_color;
	int		c_color;
}	t_data;

/* TIME */
void	set_delta_time(t_game *game);
double	get_time_in_seconds(void);
void	limit_fps(double target_fps);

/* FILE PARSING */
int		parse_given_file(char *file);
int		parse_given_fd(int file_fd);
int		parse_file(int map_fd, char **config, char **symbols, int i);
int		parse_fc_colors(char ***config);
int		parse_map(int file_fd);
char	*rgb_to_hex(int rgb);
int		hex_str_to_int(char *str, char *hex);
int		compare_symbols(char *str, char **symbols);
int		free_all(char **textures_matrix, char ***textures_array, char *error_msg);
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
char	**fill_in_with_x(void);
void	ft_flood_fill(char **map, int x, int y, int *valid_map);

/* ERROR */
int		print_error(char *error_message);
int		print_perror(void);

/* CORE */
t_data	*get_data(void);

#endif
