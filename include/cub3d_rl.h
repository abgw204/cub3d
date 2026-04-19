#ifndef CUB3D_RL_H
# define CUB3D_RL_H

# include "cub3d.h"

# include <arpa/inet.h>
# include <sys/socket.h>

# include "raylib.h"

# if defined(__GNUC__) || defined(__clang__)
#  define CUB3D_PACKED __attribute__((packed))
# else
#  define CUB3D_PACKED
# endif

// --- Raylib-only types ---

typedef struct s_rl_tex
{
	Texture2D	no;
	Texture2D	so;
	Texture2D	we;
	Texture2D	ea;
} 	t_rl_tex;

typedef struct s_gun_anim
{
	int		frame;
	float	acc;
} 	t_gun_anim;

typedef struct s_rl_assets
{
	t_rl_tex	walls;
	Texture2D	enemy;
	Texture2D	gun_sheet;
	Sound		gunshot;
	bool		audio_ok;
} 	t_rl_assets;

typedef struct s_rl_scene
{
	RenderTexture2D	target;
	int				w;
	int				h;
} 	t_rl_scene;

typedef struct s_rl_ctx
{
	t_game		*game;
	t_rl_assets	assets;
	t_rl_scene	scene;
	t_gun_anim	gun_anim;
	bool		prev_dead;
	bool		want_respawn;
	int			server_port;
	char			server_ip[64];
} 	t_rl_ctx;

// --- Network packets (wire format) ---

// Input packet is 17 bytes.
// Layout matches legacy: [0..3]=keys, [4..7]=id, [8..15]=angle, [16]=event
typedef struct s_net_input
{
	char	keys[4];
	int		id;
	double	angle;
	char	event;
} CUB3D_PACKED 	t_net_input;

// State packet entry is 28 bytes.
// Layout: id(int), x(double), y(double), connected(int), health(int)
typedef struct s_net_state
{
	int		id;
	double	x;
	double	y;
	int		connected;
	int		health;
} CUB3D_PACKED 	t_net_state;

// --- App lifecycle ---

int		rl_app_init(t_rl_ctx *ctx, const char *map_path, int my_id, const char *server_ip, int port);
void	rl_app_tick(t_rl_ctx *ctx);
void	rl_app_shutdown(t_rl_ctx *ctx);

// --- Render ---

void	rl_render_scene(t_rl_ctx *ctx);
void	rl_render_sprites(t_rl_ctx *ctx);

// --- Networking ---

int		rl_net_init(t_game *game, int my_id, const char *server_ip, int port);
void	rl_net_send_inputs(t_game *game);
void	rl_net_receive_state(t_game *game);

// --- Input/UI ---

void	rl_input_update(t_rl_ctx *ctx);
bool	rl_ui_draw_death_overlay(int screen_w, int screen_h);

// --- Assets ---

int		rl_assets_load(t_rl_assets *a, t_data *data);
void	rl_assets_unload(t_rl_assets *a);

// --- Utils ---

RenderTexture2D	rl_create_scene_target(int screen_w, int screen_h);
int		rl_clampi(int v, int lo, int hi);
Color	rl_color_from_hex_rgb(int hex);

#endif
