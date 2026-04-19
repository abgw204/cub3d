#ifndef RL_PLATFORM_H
# define RL_PLATFORM_H

# include "cub3d_platform.h"

int	rl_platform_net_startup(void);
void	rl_platform_net_cleanup(void);
int	rl_platform_socket_set_nonblocking(cub3d_socket_t s);
void	rl_platform_socket_close(cub3d_socket_t s);

#endif
