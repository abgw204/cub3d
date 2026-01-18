/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_images.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:35:59 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/12 11:49:22 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	set_textures_images_info(t_game *game)
{
	game->n.addr = mlx_get_data_addr(game->n.img, &game->n.bpp,
			&game->n.line_len, &game->n.endian);
	game->s.addr = mlx_get_data_addr(game->s.img, &game->s.bpp,
			&game->s.line_len, &game->s.endian);
	game->w.addr = mlx_get_data_addr(game->w.img, &game->w.bpp,
			&game->w.line_len, &game->w.endian);
	game->e.addr = mlx_get_data_addr(game->e.img, &game->e.bpp,
			&game->e.line_len, &game->e.endian);
	game->door.addr = mlx_get_data_addr(game->door.img,
			&game->door.bpp, &game->door.line_len, &game->door.endian);
}

int	check_images(t_game *game)
{
	if (!game->n.img || !game->s.img || !game->w.img || !game->e.img
		|| !game->door.img)
	{
		if (game->n.img)
			mlx_destroy_image(game->mlx, game->n.img);
		if (game->s.img)
			mlx_destroy_image(game->mlx, game->s.img);
		if (game->w.img)
			mlx_destroy_image(game->mlx, game->w.img);
		if (game->e.img)
			mlx_destroy_image(game->mlx, game->e.img);
		if (game->door.img)
			mlx_destroy_image(game->mlx, game->door.img);
		game->n.img = NULL;
		game->s.img = NULL;
		game->w.img = NULL;
		game->e.img = NULL;
		game->door.img = NULL;
		return (print_error("One or more textures failed to load!"));
	}
	return (0);
}

static int	get_texture_dir(char ***config, const char *dir)
{
	int		i;

	i = 0;
	while (config[i])
	{
		if (!ft_strcmp(config[i][0], dir))
			return (i);
		i++;
	}
	return (-1);
}

static int	load_textures_images(t_game *game)
{
	int	tex;

	tex = get_texture_dir(game->data->config, "NO");
	game->n.img = mlx_xpm_file_to_image(game->mlx,
			game->data->config[tex][1], &game->n.width,
			&game->n.height);
	tex = get_texture_dir(game->data->config, "SO");
	game->s.img = mlx_xpm_file_to_image(game->mlx,
			game->data->config[tex][1], &game->s.width,
			&game->s.height);
	tex = get_texture_dir(game->data->config, "EA");
	game->e.img = mlx_xpm_file_to_image(game->mlx,
			game->data->config[tex][1], &game->e.width,
			&game->e.height);
	tex = get_texture_dir(game->data->config, "WE");
	game->w.img = mlx_xpm_file_to_image(game->mlx,
			game->data->config[tex][1], &game->w.width,
			&game->w.height);
	if (check_images(game))
		return (1);
	return (0);
}

int	configure_textures_images(t_game *game)
{
	game->door.img = mlx_xpm_file_to_image(game->mlx,
			"bonus/res/textures/sprites/door_spritesheet.xpm",
			&game->door.width, &game->door.height);
	if (load_textures_images(game))
		return (1);
	if (game->door.width / 6 != 64 || game->door.height != 64)
	{
		if (check_images(game))
		{
			ft_putendl_fd("Invalid door spritesheet (nice try)", 2);
			return (1);
		}
	}
	set_textures_images_info(game);
	return (0);
}
