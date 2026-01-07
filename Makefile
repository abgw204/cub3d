CC = cc
FLAGS = -g -Wall -Wextra -Werror

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

FUNCTIONS_BONUS = bonus/src/parsing/parsing.c \
				bonus/src/parsing/parsing_utils.c \
				bonus/src/parsing/parse_file.c \
				bonus/src/parsing/parse_fc_colors.c \
				bonus/src/parsing/parse_map_flood_fill.c \
				bonus/src/parsing/free_all.c \
				bonus/src/parsing/compare_symbols.c \
				bonus/src/parsing/parse_map.c \
				bonus/src/parsing/parse_map_utils.c \
				bonus/src/parsing/hex_int_conversions.c \
				bonus/src/parsing/get_player_info.c \
				bonus/src/error/error.c \
				bonus/src/load_images/main_menu_images.c \
				bonus/src/load_images/load_screen_image.c \
				bonus/src/load_images/settings_images.c \
				bonus/src/load_images/load_textures_images.c \
				bonus/src/time/delta_time.c \
				bonus/src/free/free_and_exit.c \
				bonus/src/time/limit_fps.c \
				bonus/src/game/menu_screen/main_menu.c \
				bonus/src/game/minimap/minimap.c \
				bonus/src/game/minimap/minimap_utils.c \
				bonus/src/game/door/update_door.c \
				bonus/src/game/menu_screen/set_img_info.c \
				bonus/src/game/menu_screen/settings.c \
				bonus/src/hooks/mouse_handler/mouse.c \
				bonus/src/hooks/menu.c \
				bonus/src/hooks/keyboard_inputs/keyboard_handler.c \
				bonus/src/render/draw/draw_pixel_in_image.c \
				bonus/src/render/draw/draw_sprites.c \
				bonus/src/render/raycast/raycast.c \
				bonus/src/render/raycast/raycast_door.c \
				bonus/src/render/raycast/cast_door_rays.c \
				bonus/src/render/raycast/texture_utils.c \
				bonus/src/render/raycast/threads_cond.c \
				bonus/src/render/raycast/cast_rays_and_draw.c \
				bonus/src/render/raycast/getters_setters.c \
				bonus/src/game/start/init_game.c \
				bonus/src/game/start/init_game_utils.c \
				bonus/src/game/game_loop/game_loop.c \
				bonus/src/game/utils/mouse_utils.c \
				bonus/src/game/player/move_player.c \
				bonus/src/game/player/rotate_camera.c \
				bonus/src/load_images/load_weapon_images.c \
				bonus/src/render/raycast/draw_utils.c \
				bonus/src/parsing/parse_doors.c

OBJS = $(FUNCTIONS:.c=.o)

OBJS_BONUS = $(FUNCTIONS_BONUS:.c=.o)

NAME = cub3D

NAME_BONUS = cub3D_bonus

.c.o:
	@echo -n "|"
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME_LIB) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(FLAGS) src/main.c $(OBJS) -Llib/libft -lft -Llib/minilibx-linux -lmlx_Linux -lX11 -lXext -lm -o $(NAME)
	@echo "\033[46mcub3d compiled successfully!\033[0m"

$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT)
	@$(CC) $(FLAGS) bonus/src/main_bonus.c $(OBJS_BONUS) -Llib/libft -lft -Llib/minilibx-linux -lmlx_Linux -lX11 -lXext -lm -o $(NAME_BONUS)
	@echo
	@echo "\033[46mcub3d bonus compiled successfully!\033[0m"

$(LIBFT):
	@echo
	@make -C lib/libft --no-print-directory

clean:
	@rm -f $(OBJS) $(OBJS_BONUS) $(OBJS_SERVER)
	@make clean -C lib/libft --no-print-directory

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS) $(NAME_LIB) $(NAME_LIB_BONUS) $(SERVER_NAME)
	@make fclean -C lib/libft --no-print-directory

re: fclean all

bonus: $(NAME_BONUS)
