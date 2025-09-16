#include "../include/cub3d.h"

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	if (parse_map_file(argv[1]))
		return (1);
	return (0);
}
