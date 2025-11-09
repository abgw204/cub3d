/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures_images.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/06 16:35:59 by gada-sil          #+#    #+#             */
/*   Updated: 2025/11/06 17:47:22 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	check_images(t_game *game)
{
	if (!game->n.img || !game->s.img || !game->w.img || !game->e.img)
	{
		if (game->n.img)
			mlx_destroy_image(game->mlx, game->n.img);
		if (game->s.img)
			mlx_destroy_image(game->mlx, game->s.img);
		if (game->w.img)
			mlx_destroy_image(game->mlx, game->w.img);
		if (game->e.img)
			mlx_destroy_image(game->mlx, game->e.img);
		game->n.img = NULL;
		game->s.img = NULL;
		game->w.img = NULL;
		game->e.img = NULL;
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
	game->data->config[tex][1],
	&game->n.width,
	&game->n.height);
	tex = get_texture_dir(game->data->config, "SO");
	game->s.img = mlx_xpm_file_to_image(game->mlx,
	game->data->config[tex][1],
	&game->s.width,
	&game->s.height);
	tex = get_texture_dir(game->data->config, "EA");
	game->e.img = mlx_xpm_file_to_image(game->mlx,
	game->data->config[tex][1],
	&game->e.width,
	&game->e.height);
	tex = get_texture_dir(game->data->config, "WE");
	game->w.img = mlx_xpm_file_to_image(game->mlx,
	game->data->config[tex][1],
	&game->w.width,
	&game->w.height);
	if (check_images(game))
		return (1);
	return (0);
}

int	configure_textures_images(t_game *game)
{
	if (load_textures_images(game))
		return (1);
	return (0);
}
