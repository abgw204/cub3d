/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_player_info.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:00:22 by gada-sil          #+#    #+#             */
/*   Updated: 2025/11/04 20:31:52 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	set_pos(t_game *game, int x, int y)
{
	t_dv2	pos;

	pos.x = (double)x + 0.5;
	pos.y = (double)y + 0.5;
	game->player.pos = pos;
	printf("PlayerX: %.2f | PlayerY: %.2f\n", game->player.pos.x, game->player.pos.y);
}

static void	set_dir(t_game *game, char dir)
{
	if (dir == 'N')
	{
		game->player.dir.x = 0.0;
		game->player.dir.y = -1.0;
		game->player.plane.x = 0.66;
		game->player.plane.y = 0.00;
		game->player.angle = -PI / 2;
	}
	else if (dir == 'S')
	{
		game->player.dir.x = 0.0;
		game->player.dir.y = 1.0;
		game->player.plane.x = -0.66;
		game->player.plane.y = 0.0;
		game->player.angle = PI / 2;
	}
	else if (dir == 'E')
	{
		game->player.dir.x = 1.0;
		game->player.dir.y = 0.0;
		game->player.plane.x = 0.0;
		game->player.plane.y = 0.66;
		game->player.angle = 0;
	}
	else if (dir == 'W')
	{
		game->player.dir.x = -1.0;
		game->player.dir.y = 0.0;
		game->player.plane.x = 0;
		game->player.plane.y = -0.66;
		game->player.angle = PI;
	}
	printf("DirX: %.2f | dirY: %.2f [%c]\n", game->player.dir.x,
		game->player.dir.y, dir);
}

void	get_player_info(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < game->map_h)
	{
		while (++j < game->map_w)
		{
			if (game->map[i * game->map_w + j] == 'N'
				|| game->map[i * game->map_w + j] == 'S'
				|| game->map[i * game->map_w + j] == 'W'
				|| game->map[i * game->map_w + j] == 'E')
			{
				set_pos(game, j, i);
				set_dir(game, game->map[i * game->map_w + j]);
				break ;
			}
		}
		j = -1;
	}
}
