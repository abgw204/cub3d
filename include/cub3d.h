#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include "libft.h"

int		parse_map_file(char *file);
int		print_error(char *error_message);
int		print_perror(void);

#endif
