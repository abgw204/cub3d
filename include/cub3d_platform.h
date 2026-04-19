#ifndef CUB3D_PLATFORM_H
# define CUB3D_PLATFORM_H

# ifdef _WIN32
#  ifndef WIN32_LEAN_AND_MEAN
#   define WIN32_LEAN_AND_MEAN
#  endif

// Prevent WinAPI from defining common names that conflict with raylib.
// - Rectangle() (GDI) conflicts with raylib's Rectangle type.
// - CloseWindow/ShowCursor/LoadImage/DrawText (USER32) conflict with raylib APIs.
#  ifndef NOMINMAX
#   define NOMINMAX
#  endif
#  ifndef NOGDI
#   define NOGDI
#  endif
#  ifndef NOUSER
#   define NOUSER
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
