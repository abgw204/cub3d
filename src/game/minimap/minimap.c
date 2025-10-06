/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:19 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/30 14:57:35 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	draw_block(t_image *minimap, t_vector2 pos, int size, int color)
{
	int	i;
	int	j;

	i = (int)pos.x;
	j = (int)pos.y;
	while (i < pos.x + size)
	{
		while (j < pos.y + size)
			draw_pixel_in_image(minimap, j++, i, color);
		j = (int)pos.y;
		i++;
	}
}

void	clear_minimap(t_image *minimap)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < minimap->height)
	{
		while (++j < minimap->width)
			draw_pixel_in_image(minimap, i, j, 0x666666);
		j = -1;
	}
}

int	load_minimap(t_game *game)
{
	t_vector2	p_pos;

	p_pos.x = 105;
	p_pos.y = 105;
	game->minimap.img = mlx_new_image(game->mlx, 200, 200);
	if (!game->minimap.img)
		return (print_error("Minimap failed to be created!"));
	game->minimap.addr = mlx_get_data_addr(game->minimap.img,
										&game->minimap.bpp,
										&game->minimap.line_len,
										&game->minimap.endian);
	game->minimap.width = 200;
	game->minimap.height = 200;
	clear_minimap(&game->minimap);
	draw_block(&game->minimap, p_pos, 10, 0x00AA00);
	return (0);
}

void	draw_minimap(t_game *game)
{
	t_vector2	minipos;
	int			x_bg;
	int			x_end;
	int			y_bg;
	int			y_end;
	t_player	player;

	char map[7][20] =
		{
			"1111111111111111111",
			"1000000000000000001",
			"1000000000000000001",
			"1000000000000000001",
			"1000000000000000001",
			"1000000000000000001",
			"1111111111111111111"
		};
	game->map_h = 7;
	game->map_w = 20;
	minipos.x = 0;
	minipos.y = 0;
	player = game->player;
	x_bg = player.pos.x - 5;
	y_bg = player.pos.y - 5;
	x_end = player.pos.x + 5;
	y_end = player.pos.y + 5;
	while (x_bg < x_end)
	{
		while (y_bg < y_end)
		{
			if (minipos.x == 100 && minipos.y == 100)
			{
				draw_block(&game->minimap, minipos, 20, 0x5555AA);
				draw_block(&game->minimap, minipos, 10, 0x00AA00);
			}
			else if (x_bg >= 0 && y_bg >= 0 && map[x_bg][y_bg] == '0')
				draw_block(&game->minimap, minipos, 20, 0x5555AA);
			else if (x_bg >= 0 && y_bg >= 0 && map[x_bg][y_bg] == '1')
				draw_block(&game->minimap, minipos, 20, 0xAAAAFF);
			if (x_bg < 0 || y_bg < 0 || x_bg >= game->map_h || y_bg >= game->map_w)
				draw_block(&game->minimap, minipos, 20, 0x666666);
			y_bg++;
			minipos.y += 20;
		}
		minipos.y = 0;
		minipos.x += 20;
		y_bg = player.pos.y - 5;
		x_bg++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->minimap.img, 200, 200);
}
