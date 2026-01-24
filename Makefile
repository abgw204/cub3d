CC = cc
FLAGS = -g -Wall -Wextra -Werror

LIBFT = lib/libft/libft.a

FUNCTIONS = mandatory/src/parsing/parsing.c \
			mandatory/src/parsing/parsing_utils.c \
			mandatory/src/parsing/parse_file.c \
			mandatory/src/parsing/parse_fc_colors.c \
			mandatory/src/parsing/parse_map_flood_fill.c \
			mandatory/src/parsing/free_all.c \
			mandatory/src/parsing/compare_symbols.c \
			mandatory/src/parsing/parse_map.c \
			mandatory/src/parsing/parse_map_utils.c \
			mandatory/src/parsing/hex_int_conversions.c \
			mandatory/src/parsing/get_player_info.c \
			mandatory/src/error/error.c \
			mandatory/src/load_images/main_menu_images.c \
			mandatory/src/load_images/load_screen_image.c \
			mandatory/src/load_images/settings_images.c \
			mandatory/src/load_images/load_textures_images.c \
			mandatory/src/time/delta_time.c \
			mandatory/src/free/free_and_exit.c \
			mandatory/src/time/limit_fps.c \
			mandatory/src/game/menu_screen/main_menu.c \
			mandatory/src/game/menu_screen/set_img_info.c \
			mandatory/src/game/menu_screen/settings.c \
			mandatory/src/hooks/mouse_handler/mouse.c \
			mandatory/src/hooks/menu.c \
			mandatory/src/hooks/keyboard_inputs/keyboard_handler.c \
			mandatory/src/render/draw/draw_square.c \
			mandatory/src/render/draw/draw_sprites.c \
			mandatory/src/render/raycast/raycast.c \
			mandatory/src/render/raycast/cast_rays_and_draw.c \
			mandatory/src/game/start/init_game.c \
			mandatory/src/game/start/init_game_utils.c \
			mandatory/src/game/game_loop/game_loop.c \
			mandatory/src/game/utils/mouse_utils.c \
			mandatory/src/game/player/move_player.c \
			mandatory/src/game/player/rotate_camera.c \
			mandatory/src/load_images/load_weapon_images.c \
			mandatory/src/render/raycast/draw_utils.c \
			mandatory/src/render/raycast/texture_utils.c

FUNCTIONS_BONUS = bonus/src/parsing/parsing_bonus.c \
			bonus/src/parsing/parsing_utils_bonus.c \
			bonus/src/parsing/parse_file_bonus.c \
			bonus/src/parsing/parse_fc_colors_bonus.c \
			bonus/src/parsing/parse_map_flood_fill_bonus.c \
			bonus/src/parsing/free_all_bonus.c \
			bonus/src/parsing/compare_symbols_bonus.c \
			bonus/src/parsing/parse_map_bonus.c \
			bonus/src/parsing/parse_map_utils_bonus.c \
			bonus/src/parsing/hex_int_conversions_bonus.c \
			bonus/src/parsing/get_player_info_bonus.c \
			bonus/src/error/error_bonus.c \
			bonus/src/load_images/main_menu_images_bonus.c \
			bonus/src/load_images/load_screen_image_bonus.c \
			bonus/src/load_images/settings_images_bonus.c \
			bonus/src/load_images/load_textures_images_bonus.c \
			bonus/src/time/delta_time_bonus.c \
			bonus/src/free/free_and_exit_bonus.c \
			bonus/src/time/limit_fps_bonus.c \
			bonus/src/game/menu_screen/main_menu_bonus.c \
			bonus/src/game/minimap/minimap_bonus.c \
			bonus/src/game/minimap/minimap_utils_bonus.c \
			bonus/src/game/door/update_door_bonus.c \
			bonus/src/game/menu_screen/set_img_info_bonus.c \
			bonus/src/game/menu_screen/settings_bonus.c \
			bonus/src/hooks/mouse_handler/mouse_bonus.c \
			bonus/src/hooks/menu_bonus.c \
			bonus/src/hooks/keyboard_inputs/keyboard_handler_bonus.c \
			bonus/src/render/draw/draw_square_bonus.c \
			bonus/src/render/draw/draw_sprites_bonus.c \
			bonus/src/render/raycast/raycast_bonus.c \
			bonus/src/render/raycast/raycast_door_bonus.c \
			bonus/src/render/raycast/cast_door_rays_bonus.c \
			bonus/src/render/raycast/texture_utils_bonus.c \
			bonus/src/render/raycast/threads_cond_bonus.c \
			bonus/src/render/raycast/cast_rays_and_draw_bonus.c \
			bonus/src/render/raycast/getters_setters_bonus.c \
			bonus/src/render/raycast/get_int_and_increment_bonus.c \
			bonus/src/game/start/init_game_bonus.c \
			bonus/src/game/start/init_game_utils_bonus.c \
			bonus/src/game/game_loop/game_loop_bonus.c \
			bonus/src/game/utils/mouse_utils_bonus.c \
			bonus/src/game/player/move_player_bonus.c \
			bonus/src/game/player/rotate_camera_bonus.c \
			bonus/src/load_images/load_weapon_images_bonus.c \
			bonus/src/render/raycast/draw_utils_bonus.c \
			bonus/src/parsing/parse_doors_bonus.c

OBJS = $(FUNCTIONS:.c=.o)

OBJS_BONUS = $(FUNCTIONS_BONUS:.c=.o)

NAME = cub3D

NAME_BONUS = cub3D_bonus

.c.o:
	@echo -n "|"
	@$(CC) $(FLAGS) -c $< -o $@

all: $(NAME_LIB) $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(FLAGS) mandatory/src/main.c $(OBJS) -Llib/libft -lft -Llib/minilibx-linux -lmlx_Linux -lX11 -lXext -lm -o $(NAME)
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
