CC = cc
FLAGS = -g -Wall -Wextra -Werror -Wno-cast-function-type

LIBFT = lib/libft/libft.a

# Sources for the raylib client (no MLX usage).
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
			src/rl/rl_error.c \
			src/rl/rl_utils.c \
			src/rl/rl_assets.c \
			src/rl/rl_net.c \
			src/rl/rl_input.c \
			src/rl/rl_ui.c \
			src/rl/rl_render_world.c \
			src/rl/rl_render_sprites.c \
			src/rl/rl_app.c

OBJS_RL = $(FUNCTIONS_RL:.c=.o)

# Raylib-only objects need raylib headers.
$(OBJS_RL): FLAGS += -DCUB3D_NO_MLX $(RAYLIB_CFLAGS)

FUNCTIONS_SERVER = server/src/init.c \
					server/src/time.c \
					server/src/parse_map_server.c \
					server/src/parse_map_s_utils.c

OBJS_SERVER = $(FUNCTIONS_SERVER:.c=.o)

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

SERVER_NAME = server_cub3d

.c.o:
	@echo -n "|"
	@$(CC) $(FLAGS) -c $< -o $@

all: rl


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

bonus:
	@printf "bonus target removed (MLX version was deleted)\n" && false

$(LIBFT):
	@echo
	@make -C lib/libft --no-print-directory

$(SERVER_NAME): $(OBJS_SERVER) $(LIBFT)
	@$(CC) $(FLAGS) server/src/main.c -lm $(OBJS_SERVER) -Llib/libft -lft -o $(SERVER_NAME)
	@echo "\033[46mcub3d server compiled successfully!\033[0m"

server: $(SERVER_NAME)

clean:
	@rm -f $(OBJS_SERVER) $(OBJS_RL)
	@make clean -C lib/libft --no-print-directory

fclean: clean
	@rm -f $(SERVER_NAME) $(NAME_RL)
	@make fclean -C lib/libft --no-print-directory

re: fclean all
