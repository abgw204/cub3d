cmake_minimum_required(VERSION 3.20)

project(cub3d C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

# --- raylib ---
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)

add_subdirectory(third_party/raylib EXCLUDE_FROM_ALL)

# --- libft ---
file(GLOB_RECURSE LIBFT_SOURCES CONFIGURE_DEPENDS
  "${CMAKE_SOURCE_DIR}/lib/libft/*.c"
)

add_library(ft STATIC ${LIBFT_SOURCES})
target_include_directories(ft PUBLIC
  "${CMAKE_SOURCE_DIR}/include"
  "${CMAKE_SOURCE_DIR}/lib/libft"
  "${CMAKE_SOURCE_DIR}/lib/libft/get_next_line"
  "${CMAKE_SOURCE_DIR}/lib/libft/ft_printf"
)

# --- cub3d_rl ---
set(CUB3D_RL_SOURCES
  src/main_raylib.c
  src/parsing/parsing.c
  src/parsing/parsing_utils.c
  src/parsing/parse_file.c
  src/parsing/parse_fc_colors.c
  src/parsing/parse_map_flood_fill.c
  src/parsing/free_all.c
  src/parsing/compare_symbols.c
  src/parsing/parse_map.c
  src/parsing/parse_map_utils.c
  src/parsing/hex_int_conversions.c
  src/parsing/get_player_info.c
  src/time/delta_time.c
  src/time/limit_fps.c
  src/rl/rl_error.c
  src/rl/rl_utils.c
  src/rl/rl_assets.c
  src/rl/rl_net.c
  src/rl/rl_input.c
  src/rl/rl_ui.c
  src/rl/rl_render_world.c
  src/rl/rl_render_sprites.c
  src/rl/rl_app.c
  src/rl/rl_platform.c
)

add_executable(cub3d_rl ${CUB3D_RL_SOURCES})
target_include_directories(cub3d_rl PRIVATE
  "${CMAKE_SOURCE_DIR}/include"
)
target_compile_definitions(cub3d_rl PRIVATE CUB3D_NO_MLX)
target_compile_options(cub3d_rl PRIVATE -Wall -Wextra -Werror -Wno-cast-function-type)
target_link_libraries(cub3d_rl PRIVATE raylib ft)

if (NOT WIN32)
  target_link_libraries(cub3d_rl PRIVATE m)
else()
  target_link_libraries(cub3d_rl PRIVATE ws2_32)
endif()

# --- Packaging (zip) ---
add_custom_target(package_zip
  DEPENDS cub3d_rl
  COMMAND ${CMAKE_COMMAND} -E rm -rf "${CMAKE_BINARY_DIR}/cub3d_package"
  COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_BINARY_DIR}/cub3d_package"
  COMMAND ${CMAKE_COMMAND} -E copy "$<TARGET_FILE:cub3d_rl>" "${CMAKE_BINARY_DIR}/cub3d_package/"
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_SOURCE_DIR}/res" "${CMAKE_BINARY_DIR}/cub3d_package/res"
  COMMAND ${CMAKE_COMMAND} -E tar "cf" "${CMAKE_BINARY_DIR}/cub3d_rl_${CMAKE_SYSTEM_NAME}.zip" --format=zip "${CMAKE_BINARY_DIR}/cub3d_package"
  VERBATIM
)
