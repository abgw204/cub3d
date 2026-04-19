#ifndef CUB3D_PLATFORM_H
# define CUB3D_PLATFORM_H

# ifdef _WIN32
#  ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#  endif
#  include <winsock2.h>
#  include <ws2tcpip.h>

typedef SOCKET	cub3d_socket_t;
typedef int		cub3d_socklen_t;

#  define CUB3D_INVALID_SOCKET INVALID_SOCKET

# else

#  include <arpa/inet.h>
#  include <netinet/in.h>
#  include <sys/socket.h>

typedef int			cub3d_socket_t;
typedef socklen_t	cub3d_socklen_t;

#  define CUB3D_INVALID_SOCKET (-1)

# endif

#endif
