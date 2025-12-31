CC = cc
FLAGS = -g -Wall -Wextra -Werror -Wno-cast-function-type

LIBFT = lib/libft/libft.a

FUNCTIONS = src/parsing/parsing.c \
			src/parsing/parsing_utils.c \
			src/parsing/parse_file.c \
			src/parsing/parse_fc_colors.c \
			src/parsing/parse_map_flood_fill.c \
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

FUNCTIONS_BONUS =

FUNCTIONS_SERVER = server/src/init.c \
					server/src/time.c \
					server/src/parse_map_server.c \
					server/src/parse_map_s_utils.c

OBJS = $(FUNCTIONS:.c=.o)

OBJS_BONUS = $(FUNCTIONS_BONUS:.c=.o)

OBJS_SERVER = $(FUNCTIONS_SERVER:.c=.o)

NAME = cub3d

NAME_BONUS = cub3d_bonus

SERVER_NAME = server_cub3d

.c.o:
	@echo -n "|"
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME_LIB) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(FLAGS) src/main.c $(OBJS) -Llib/libft -lft -Llib/minilibx-linux -lmlx_Linux -lX11 -lXext -lm -o $(NAME)
	@echo "\033[46mcub3d compiled successfully!\033[0m"

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
	@rm -f $(NAME) $(NAME_BONUS) $(NAME_LIB) $(NAME_LIB_BONUS) $(SERVER_NAME)
	@make fclean -C lib/libft --no-print-directory

re: fclean all

bonus: $(NAME_BONUS)
