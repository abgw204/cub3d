CC = cc
FLAGS = -g -Wall -Wextra -Werror

LIBFT = lib/libft/libft.a

FUNCTIONS = src/parsing/parsing.c \
			src/parsing/parsing_utils.c \
			src/parsing/parse_file.c \
			src/parsing/parse_fc_colors.c \
			src/parsing/free_all.c \
			src/parsing/compare_symbols.c \
			src/parsing/parse_map.c \
			src/parsing/hex_int_conversions.c \
			src/error/error.c \
			src/load_images/main_menu_images.c \
			src/load_images/settings_images.c \
			src/time/delta_time.c \
			src/free/free_and_exit.c \
			src/time/limit_fps.c \
			src/game/menu_screen/main_menu.c \
			src/game/menu_screen/set_img_info.c \
			src/game/menu_screen/settings.c \
			src/hooks/mouse_handler/mouse.c \
			src/hooks/menu.c \
			src/render/draw/draw_pixel_in_image.c \
			src/game/start/init_game.c

FUNCTIONS_BONUS =

OBJS = $(FUNCTIONS:.c=.o)

OBJS_BONUS = $(FUNCTIONS_BONUS:.c=.o)

NAME = cub3d

NAME_BONUS = cub3d_bonus

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

clean:
	@rm -f $(OBJS) $(OBJS_BONUS)
	@make clean -C lib/libft --no-print-directory

fclean: clean
	@rm -f $(NAME) $(NAME_BONUS) $(NAME_LIB) $(NAME_LIB_BONUS)
	@make fclean -C lib/libft --no-print-directory

re: fclean all

bonus: $(NAME_BONUS)
