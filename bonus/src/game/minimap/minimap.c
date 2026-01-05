/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:19 by gada-sil          #+#    #+#             */
/*   Updated: 2025/11/05 03:47:03 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static void	draw_block(t_image *minimap, t_iv2 pos, int size, int color)
{
	char	*dst;
	int		pitch;
	int		i;
	int		j;

	pitch = minimap->bpp >> 3;
	i = pos.x;
	j = pos.y;
	while (i < pos.x + size)
	{
		while (j < pos.y + size)
		{
			dst = minimap->addr
				+ j++ * minimap->line_len
				+ i * pitch;
			*(unsigned int*)dst = color;
		}
		j = pos.y;
		i++;
	}
}

static void	draw_player(t_game *game, t_iv2 minipos)
{
	float	decimal_x;
	float	decimal_y;
	int		gap_x;
	int		gap_y;

	decimal_x = game->player.pos.x * 10.0f;
	decimal_y = game->player.pos.y * 10.0f;
	gap_x = (int)decimal_x % 10;
	gap_y = (int)decimal_y % 10;
	minipos.x += gap_x;
	minipos.y += gap_y;
	draw_block(&game->minimap.img, minipos, 9, 0x00AA00);
}


static void	draw_in_minimap(t_minimap *mini, t_game *game, char *map)
{
	char	map_c;

	map_c = 'X';
	if (in_bounds(mini->x_bg, mini->y_bg, game->map_w, game->map_h))
		map_c = map[mini->y_bg * game->map_w + mini->x_bg];
	if (!in_bounds(mini->x_bg, mini->y_bg, game->map_w, game->map_h)
		|| map_c == 'X' || map_c == ' ')
	{
		draw_block(&mini->img, mini->pos, 20, 0x5555AA);
		return ;
	}
	if (mini->pos.x == 100 && mini->pos.y == 100)
	{
		draw_block(&mini->img, mini->pos, 20, BLACK);
		draw_player(game, mini->pos);
	}
	else if (in_bounds(mini->x_bg, mini->y_bg, game->map_w, game->map_h)
		&& map_c == '1')
		draw_block(&mini->img, mini->pos, 20, 0x5555AA);
	else if (in_bounds(mini->x_bg, mini->y_bg, game->map_w, game->map_h)
		&& (map_c == '0' || map_c == 'N' || map_c == 'S' || map_c == 'W'
			|| map_c == 'E' || map_c == 'D'))
		draw_block(&mini->img, mini->pos, 20, BLACK);
}

int	load_minimap(t_game *game)
{
	game->minimap.img.img = mlx_new_image(game->mlx, 200, 200);
	if (!game->minimap.img.img)
		return (print_error("Minimap failed to be created!"));
	game->minimap.img.addr = mlx_get_data_addr(game->minimap.img.img,
			&game->minimap.img.bpp,
			&game->minimap.img.line_len,
			&game->minimap.img.endian);
	game->minimap.img.width = 200;
	game->minimap.img.height = 200;
	return (0);
}

void	draw_minimap(t_game *game)
{
	t_minimap	*mini;

	mini = &game->minimap;
	init_mini(mini, game);
	while (mini->y_bg < mini->y_end)
	{
		while (mini->x_bg < mini->x_end)
		{
			draw_in_minimap(mini, game, game->map);
			mini->x_bg++;
			mini->pos.x += 20;
		}
		mini->pos.x = 0;
		mini->x_bg = (int)game->player.pos.x - 5;
		mini->pos.y += 20;
		mini->y_bg++;
	}
	mlx_put_image_to_window(game->mlx, game->win,
		mini->img.img, 30, 60);
}
