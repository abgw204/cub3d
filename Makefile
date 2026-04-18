CC = cc
FLAGS = -g -Wall -Wextra -Werror -Wno-cast-function-type

LIBFT = lib/libft/libft.a

FUNCTIONS = src/parsing/parsing.c \
			src/parsing/parsing_utils.c \
			src/parsing/parse_file.c \
			src/parsing/parse_fc_colors.c \
			src/parsing/parse_map_flood_fill.c\
			src/parsing/free_all.c \
			src/parsing/compare_symbols.c \
			src/parsing/parse_map.c \
			src/parsing/parse_map_utils.c \
			src/parsing/hex_int_conversions.c \
			src/parsing/get_player_info.c \
			src/error/error.c \
			src/load_images/main_menu_images.c \
			src/load_images/load_screen_image.c \
			src/load_images/settings_images.c \
			src/load_images/load_textures_images.c \
			src/time/delta_time.c \
			src/free/free_and_exit.c \
			src/time/limit_fps.c \
			src/game/menu_screen/main_menu.c \
			src/game/minimap/minimap.c \
			src/game/minimap/minimap_utils.c \
			src/game/menu_screen/set_img_info.c \
			src/game/menu_screen/settings.c \
			src/hooks/mouse_handler/mouse.c \
			src/hooks/menu.c \
			src/hooks/keyboard_inputs/keyboard_handler.c \
			src/render/draw/draw_pixel_in_image.c \
			src/render/draw/draw_sprites.c \
			src/render/raycast/raycast.c \
			src/render/raycast/threads_cond.c \
			src/render/raycast/cast_rays_and_draw.c \
			src/render/raycast/getters_setters.c \
			src/game/start/init_game.c \
			src/game/start/init_game_utils.c \
			src/game/game_loop/game_loop.c \
			src/game/utils/mouse_utils.c \
			src/game/player/move_player.c \
			src/game/player/rotate_camera.c \
			src/load_images/load_weapon_images.c \
			src/render/raycast/draw_utils.c

# Sources we can build in the raylib migration binary (no MLX usage).
FUNCTIONS_RL = src/parsing/parsing.c \
			src/parsing/parsing_utils.c \
			src/parsing/parse_file.c \
			src/parsing/parse_fc_colors.c \
			src/parsing/parse_map_flood_fill.c\
			src/parsing/free_all.c \
			src/parsing/compare_symbols.c \
			src/parsing/parse_map.c \
			src/parsing/parse_map_utils.c \
			src/parsing/hex_int_conversions.c \
			src/parsing/get_player_info.c \
			src/time/delta_time.c \
			src/time/limit_fps.c \
			src/game/player/rotate_camera.c

OBJS_RL = $(FUNCTIONS_RL:.c=.o)

FUNCTIONS_BONUS =

FUNCTIONS_SERVER = server/src/init.c \
					server/src/time.c \
					server/src/parse_map_server.c \
					server/src/parse_map_s_utils.c

OBJS = $(FUNCTIONS:.c=.o)

OBJS_BONUS = $(FUNCTIONS_BONUS:.c=.o)

OBJS_SERVER = $(FUNCTIONS_SERVER:.c=.o)

NAME = cub3d

NAME_RL = cub3d_rl

PKG_CONFIG ?= pkg-config

RAYLIB_DIR = third_party/raylib
RAYLIB_BUILD_DIR = $(RAYLIB_DIR)/src
RAYLIB_A = $(RAYLIB_BUILD_DIR)/libraylib.a
RAYLIB_CFLAGS_SUBMODULE = -I$(RAYLIB_DIR)/src
RAYLIB_LDLIBS_SUBMODULE = -L$(RAYLIB_BUILD_DIR) -lraylib -lm -lpthread -ldl
# raylib desktop backend (GLFW) depends on a window system (usually X11 on Linux)
RAYLIB_LDLIBS_SUBMODULE += -lX11 -lXrandr -lXinerama -lXi -lXcursor -lXext -lGL

RAYLIB_PC_OK := $(shell $(PKG_CONFIG) --exists raylib 2>/dev/null && echo yes)

ifeq ($(RAYLIB_PC_OK),yes)
RAYLIB_CFLAGS = $(shell $(PKG_CONFIG) --cflags raylib 2>/dev/null)
RAYLIB_LDLIBS = $(shell $(PKG_CONFIG) --libs raylib 2>/dev/null)
else
RAYLIB_CFLAGS = $(RAYLIB_CFLAGS_SUBMODULE)
RAYLIB_LDLIBS = $(RAYLIB_LDLIBS_SUBMODULE)
X11_DEPS_CHECK = /usr/include/X11/extensions/Xrandr.h
endif

NAME_BONUS = cub3d_bonus

SERVER_NAME = server_cub3d

.c.o:
	@echo -n "|"
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME_LIB) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(FLAGS) src/main.c $(OBJS) -Llib/libft -lft -Llib/minilibx-linux -lmlx_Linux -lX11 -lXext -lm -o $(NAME)
	@echo "\033[46mcub3d compiled successfully!\033[0m"


ifeq ($(RAYLIB_PC_OK),yes)
raylib:
	@true
else
$(X11_DEPS_CHECK):
	@printf "\nMissing X11 development headers. Install dependencies listed in docs/raylib.md (e.g. libxrandr-dev/libXrandr-devel).\n\n" && false

$(RAYLIB_A): $(X11_DEPS_CHECK)
	@$(MAKE) -C $(RAYLIB_BUILD_DIR) PLATFORM=PLATFORM_DESKTOP RAYLIB_LIBTYPE=STATIC --no-print-directory

raylib: $(RAYLIB_A)
endif


$(NAME_RL): raylib $(OBJS_RL) $(LIBFT)
	@$(CC) $(FLAGS) -DCUB3D_NO_MLX src/main_raylib.c $(OBJS_RL) $(RAYLIB_CFLAGS) -Llib/libft -o $(NAME_RL) $(RAYLIB_LDLIBS) -lft
	@echo "\033[46m$(NAME_RL) compiled successfully!\033[0m"

rl: $(NAME_RL)

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT)
	@$(CC) $(FLAGS) main_bonus.c $(OBJS_BONUS) -Llib/libft -lft -o $(NAME_BONUS)
	@echo
	@echo "\033[46mcub3d compiled successfully!\033[0m"

$(LIBFT):
	@echo
	@make -C lib/libft --no-print-directory

$(SERVER_NAME): $(OBJS_SERVER) $(LIBFT)
	@$(CC) $(FLAGS) server/src/main.c -lm $(OBJS_SERVER) -Llib/libft -lft -o $(SERVER_NAME)
	@echo "\033[46mcub3d server compiled successfully!\033[0m"

server: $(SERVER_NAME)

clean:
	@rm -f $(OBJS) $(OBJS_BONUS) $(OBJS_SERVER)
	@make clean -C lib/libft --no-print-directory

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS) $(NAME_LIB) $(NAME_LIB_BONUS) $(SERVER_NAME) $(NAME_RL)
	@make fclean -C lib/libft --no-print-directory

re: fclean all

bonus: $(NAME_BONUS)
