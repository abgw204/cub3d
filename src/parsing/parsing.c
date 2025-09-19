#include "../../include/cub3d.h"

/*int	validate_map(int map_fd)
{

}*/

static int	invalid_extension(char *file)
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

int	parse_map_file(char *file)
{
	int		map_fd;

	if (invalid_extension(file))
		return (print_error("Invalid file extension!"));
	map_fd = open(file, O_RDONLY);
	if (map_fd < 0)
		return (print_perror());
	//if (validate_map(map_fd));
	//	return (1);
	return (0);
}
