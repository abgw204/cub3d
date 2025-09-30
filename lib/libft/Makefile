CC = cc

FLAGS = -Wall -Wextra -Werror

DIR_PRINTF = ft_printf

DIR_GNL = get_next_line

FUNCTIONS = 	ft_strdup.c \
		ft_strlen.c \
		ft_strcmp.c \
		ft_strncmp.c \
		ft_isprint.c \
		ft_tolower.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_strnstr.c \
		ft_strstr.c \
		ft_substr.c \
		ft_strtrim.c \
		ft_itoa.c \
		ft_putnbr_fd.c \
		ft_memchr.c \
		ft_memcpy.c \
		ft_putendl_fd.c \
		ft_toupper.c \
		ft_isascii.c \
		ft_atoi.c \
		ft_isalnum.c \
		ft_strchr.c \
		ft_strlcpy.c \
		ft_strrchr.c \
		ft_strjoin.c \
		ft_calloc.c \
		ft_putstr_fd.c \
		ft_putchar_fd.c \
		ft_memcmp.c \
		ft_memmove.c \
		ft_memset.c \
		ft_bzero.c \
		ft_strlcat.c \
		ft_split.c \
		ft_striteri.c \
		ft_strmapi.c \
		ft_lstnew_bonus.c \
		ft_lstsize_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstadd_back_bonus.c \
		ft_lstlast_bonus.c \
		ft_len_matrix.c \
		ft_split_utils.c \
		create_matrix.c \
		free_matrix.c \
		$(DIR_GNL)/get_next_line_utils.c \
		$(DIR_GNL)/get_next_line.c

FUNCTIONS_PRINTF = $(DIR_PRINTF)/src/ft_putnbr.c \
			$(DIR_PRINTF)/src/ft_print_pointer.c \
			$(DIR_PRINTF)/src/ft_print_hex.c \
			$(DIR_PRINTF)/src/ft_putchar.c \
			$(DIR_PRINTF)/src/ft_putstr.c \
			$(DIR_PRINTF)/src/ft_putnbr_u.c \
			$(DIR_PRINTF)/src/format.c \
			$(DIR_PRINTF)/ft_printf.c

OBJS = $(FUNCTIONS:.c=.o)

OBJS_PRINTF = $(FUNCTIONS_PRINTF:.c=.o)

NAME = libft.a

.c.o:
	@echo -n "|"
	@$(CC) $(FLAGS) -c $< -o $(<:.c=.o)
all: $(NAME)

$(NAME): $(OBJS) $(OBJS_PRINTF)
	@echo
	@ar -rc $(NAME) $(OBJS) $(OBJS_PRINTF)
clean:
	@rm -f $(OBJS) $(OBJS_PRINTF)
fclean: clean
	@rm -f $(NAME) $(OBJS) $(OBJS_PRINTF)
re: fclean all
