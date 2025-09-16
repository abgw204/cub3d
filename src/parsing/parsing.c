#include "../../include/cub3d.h"

int	invalid_extension(char *file)
{
	char	*dot;
	
	dot = ft_strrchr(file, '.');
	if (dot)
	{
		if (!ft_strcmp(++dot, "cub"))
			return (0);
	}
	return (1);
}

int	open_map(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	return (fd);
}

int	parse_map_file(char *file)
{
	int	map_fd;

	if (invalid_extension(file))
		return (print_error("Invalid file extension!"));
	map_fd = open_map(file);
	if (map_fd < 0)
		return (print_perror());
	return (0);
}
