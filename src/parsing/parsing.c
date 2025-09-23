#include "../../include/cub3d.h"

char	**parse_texture(char *texture, int i)
{
	char **matrix;

	matrix = ft_split(texture, ' ');
	if (!matrix)
		return (NULL);
	if (ft_len_matrix(matrix) != 2 || (matrix[1] && matrix[1][0] == '\n'))
		return (NULL);
	if (ft_strlen(matrix[0]) == 2)
	{
		if (matrix[0][0] == 'N' && matrix[0][1] == 'O' 
			&& i == 0)
			return (matrix);
		else if (matrix[0][0] == 'S' && matrix[0][1] == 'O' 
			&& i == 1)
			return (matrix);
		else if (matrix[0][0] == 'W' && matrix[0][1] == 'E' 
			&& i == 2)
			return (matrix);
		else if (matrix[0][0] == 'E' && matrix[0][1] == 'A' 
			&& i == 3)
			return (matrix);
	}
	return (NULL);
}

/*int	parse_fc_colors(int map_fd, char *)
{

}*/
void	initialize(char **matrix, int size)
{
	int	i;

	i = 0;
	while (i < size)
		matrix[i++] = NULL;
}

int	parse_textures(int map_fd, char **textures)
{
	int	i;

	i = -1;
	textures = (char **)malloc(5 * sizeof(char *));
	initialize(textures, 5);
	while (++i < 4)
	{
		textures[i] = get_next_line(map_fd);
		if (textures[i])
		{
			if (textures[i][0] == '\n')
			{
				free(textures[i]);
				textures[i] = NULL;
				continue ;
			}
			get_data()->textures[i] = parse_texture(textures[i], i);
			if (!get_data()->textures[i])
				return (free_matrix(textures, i));
		}
	}
	free_matrix(textures, -1);
	free_matrix(get_data()->textures[0], -1);
	free_matrix(get_data()->textures[1], -1);
	free_matrix(get_data()->textures[2], -1);
	free_matrix(get_data()->textures[3], -1);
	exit(0);
	return (0);
}

int	validate_map(int map_fd)
{
	char	**file[4];

	if (parse_textures(map_fd, file[0]))
		return (1);
	//if (parse_fc_colors(map_fd, file[1]))
	//	return (1);
	return (0);
}

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
	if (validate_map(map_fd))
		return (1);
	return (0);
}
