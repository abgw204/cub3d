/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vfidelis <vfidelis@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:13 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/09 17:51:30 by vfidelis         ###   ########.fr       */
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
# include <stdbool.h>
# include <pthread.h>
# include "../../lib/minilibx-linux/mlx.h"
# include "../../lib/libft/libft.h"

# define SCREEN_WIDTH 800
# define SCREEN_HEIGHT 800

/* KEYS */
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_E 101
# define KEY_ESC 65307

# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define UP_ARROW 65362
# define DOWN_ARROW 65364

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
# define FOV 0.75

/* MISC */
# define VERTICAL_WALL 0
# define HORIZONTAL_WALL 1
# define CONFIG_TOKENS 6
# define SHOOT_DELAY 0.3
# define COLLISION_DIST 0.3
# define DOOR_ANIM_DURATION 0.3
# define GUN_SCALE 5
# define N_THREADS 4

extern double	g_delta_time;

typedef struct	s_data t_data;
typedef struct	s_game_data t_game;

typedef struct	s_image
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

typedef struct	s_uint_vector
{
	unsigned int	x;
	unsigned int	y;
}	t_uiv2;

typedef struct	s_int_vector
{
	int	x;
	int	y;
}	t_iv2;

typedef struct	s_double_vector
{
	double	x;
	double	y;
}	t_dv2;

typedef enum	e_door_state
{
	DOOR_CLOSED,
	DOOR_OPENING,
	DOOR_OPEN,
	DOOR_CLOSING
}	t_door_state;

typedef struct s_door
{
	t_iv2			pos;
	t_door_state	state;
	double			anim_time;
	double			anim_duration;
	int				frame_count;
	int				current_frame;
}	t_door;

typedef struct	s_player
{
	t_dv2	pos;
	t_dv2	dir;
	t_dv2	plane;
	double	angle;
	double	speed;
}	t_player;

typedef struct	s_config
{
	bool	show_fps;
	bool	show_mouse;
}	t_config;

typedef struct	s_minimap
{
	int		x_bg;
	int		y_bg;
	int		x_end;
	int		y_end;
	t_iv2	pos;
	t_image	img;
}	t_minimap;

typedef struct	s_texture
{
	int		tex_x;
	int		tex_y;
	int		pitch;
	int		len;
	int		color;
	int		x_offset;
	int		height;
	int		sc_pitch;
	int		sc_line_len;
	char	*dst;
	t_image	*tex;
	double	wall_x;
	double	step;
	double	tex_pos;
}	t_texture;

typedef struct	s_gun
{
	int		sx;
	int		sy;
	int		x;
	int		y;
	int		src_w;
	int		src_h;
	int		dst_w;
	int		dst_h;
	int		bpp;
	int		line_len;
	int		color;
	int		sheet_offset;
	int		sc_offset;
	int		sc_x;
	int		sc_y;
	int		sc_line_len;
	int		sc_bpp;
	int		orig_x;
	int		orig_y;
	int		width;
	int		height;
	int		i;
	int		j;
	char	*dst;
	t_image	*tex;
}	t_gun;

typedef struct	s_game_data
{
	/* GAME */
	void			*win;
	void			*mlx;
	char			*map;
	int				map_w;
	int				map_h;
	int				m_x;
	int				m_y;
	int				state;
	char			*fps;
	char			*keys;
	bool			is_shooting;
	double			shoot_timer;
	int 			doors_n;
	t_door			*doors;
	t_player		player;
	t_minimap		minimap;
	t_config		config;
	t_data			*data;

	/* IMAGES */
	t_image			screen;
	t_image			menu_btns[4];
	t_image			settings[3];
	t_image			gun;
	t_image			n;
	t_image			s;
	t_image			e;
	t_image			w;
	t_image			door;

	/* THREADS */
	pthread_t		th[N_THREADS];
	pthread_mutex_t	m;
	pthread_cond_t	cond_start;
	pthread_cond_t	cond_done;
	int				id;
	int				threads_done;
	bool			stop;
}			t_game;

typedef struct s_data
{
	char			**config[7];
	t_list			*map_list;
	char			*map;
	int				map_w;
	int				map_h;
	int				f_color;
	int				c_color;
	int				doors_n;
	t_door			*doors;
}	t_data;

typedef struct	s_raycast
{
	double	delta_dist_x;
    double	delta_dist_y;
    double	side_dist_x;
    double	side_dist_y;
    double	perp_wall_dist;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		collum;
    int		step_y;
    int		step_x;
	int		map_x;
	int		map_y;
	int		hit;
    int		side;
	int		line_height;
    int		draw_start;
	int		draw_end;
	int		f_color;
	int		c_color;
}			t_raycast;


/* THREADS */
void	init_threads(t_game *game);
long	get_int_and_increment(pthread_mutex_t *mutex, int *variable);
int		get_int(pthread_mutex_t *mutex, int *variable);
void	increment_int(pthread_mutex_t *mutex, int *value);
void	set_int(pthread_mutex_t *mutex, int *variable, int value);
void	send_signal_to_main_thread(pthread_cond_t *done, pthread_mutex_t *m);
void	wait_signal_from_main_thread(pthread_cond_t *start, pthread_mutex_t *m);
void	start_all_render_threads(pthread_cond_t *start, pthread_mutex_t *m);
void	wait_all_render_threads(pthread_cond_t *done, pthread_mutex_t *m);
void	set_double(pthread_mutex_t *mutex, double **variable, double value, int i);
bool	get_bool(pthread_mutex_t *mutex, bool *variable);

/* TIME */
void	set_delta_time(t_game *game);
double	get_time_in_seconds(void);
void	limit_fps(double target_fps);

/* FILE PARSING */
int		parse_given_file(char *file);
int		parse_file(int map_fd, char **config, char **symbols, int i);
int		parse_fc_colors(char ***config);
int		parse_map(int file_fd);
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
char	**fill_in_with_x(void);
void	ft_flood_fill(char **map, int x, int y, int *valid_map);
int		parse_doors(char *map, int map_w, int map_h);

/* KEYBOARD*/
int	key_press(int key, void *param);
int	key_release(int key, void *param);

/* MOUSE */
int		mouse_move(int x, int y, void *param);
int		mouse_move_menu(t_game *game, int x, int y);
int		mouse_input(int mouse_btn, int x, int y, void *param);
void	enable_mouse(t_game *game);
void	disable_mouse(t_game *game);

/* MENU */
int		configure_menu_images(t_game *game);
int		load_menu_images(t_game *game);
int		configure_screen_image(t_game *game);
int		show_main_menu(t_game *game);
int		check_btn_collision(t_image *img, int x, int y);
void	set_menu_images_info(t_image *images);
int		mouse_input_menu(t_game *game, int x, int y, int mouse_btn);

/* MINIMAP */
int		load_minimap(t_game *game);
void	draw_minimap(t_game *game);
int		in_bounds(int x, int y, int endx, int endy);
void	init_mini(t_minimap *mini, t_game *game);

/* SETTINGS */
int		show_settings(t_game *game);
int		load_settings_images(t_game *game);
void	set_settings_images_info(t_image *images);
int		configure_settings_images(t_game *game);
int		mouse_move_settings(t_game *game, int x, int y);
int		mouse_input_in_settings(t_game *game, int x, int y, int mouse_btn);

/* DRAW */
void	revert_colors(t_image *image, unsigned int color1, unsigned int color2);
void	draw_ceiling(t_raycast *r, t_image *screen, int start, int limit);
void	draw_floor(t_raycast *r, t_image *screen, int start, int limit);
void	draw_circle(t_uiv2 pos, int radius, int color, t_image *image);
void	draw_square(t_iv2 pos, int size, int color, t_image *image);
void	*raycast(void *param);
void    raycast_door(t_game *game);
int		cast_door_rays(t_raycast *r, t_game *game, int start);
void	cast_rays_and_draw(t_raycast *r, t_game *game, int *start);
void	draw_sprites(t_game *game);

/* ERROR */
int		print_error(char *error_message);
int		print_error_free(t_game *game, char *error_message);
int		print_perror(void);

/* GAME */
int		init_game(t_game *game);
int		load_mlx_window(t_game *game);
int		load_weapon_images(t_game *game);
int		update(void *param);
void	move_player(t_game *game);
t_data	*get_data(void);
void	free_and_exit(t_game *game);
void	free_images(t_game *game);
int		game_loop(t_game *game);
void	rotate_camera(t_game *game);
void	rotate_camera_mouse(t_game *game, int middle, int x);
int		mouse_move_in_game(t_game *game, int x);
void	update_door(t_door *door, double dt, t_game *game, double progress);
void	toggle_door(t_door *door);
int		thread_create(pthread_t *thread, void *(func)(void *), void *data);
int		close_window_x(void *param);

/* TEXTURES */
int		configure_textures_images(t_game *game);
t_image	*get_tex(double ray_dir_x, double ray_dir_y, int side, t_game *game);
void	draw_tex(t_image *screen, t_raycast r, t_texture t, int column);
void	draw_door(t_image *screen, t_raycast r, t_texture t, int column);
int		get_door_at(t_raycast *r, t_game *game);

#endif
