#include "../../include/cub3d.h"

int	print_error(char *error_message)
{
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(error_message, 2);
	return (1);
}

int	print_perror(void)
{
	ft_putendl_fd("Error", 2);
	perror("cub3d");
	return (1);
}
