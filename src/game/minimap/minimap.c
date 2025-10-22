/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:19 by gada-sil          #+#    #+#             */
/*   Updated: 2025/10/14 15:41:18 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int	in_bounds(int x, int y, int endx, int endy)
{
	return (x >= 0 && y >= 0 && x < endx && y < endy);
}

void	draw_block(t_image *minimap, t_vector2 pos, int size, int color)
{
	int	i;
	int	j;

	i = (int)pos.x;
	j = (int)pos.y;
	printf("DRAW_BLOCK\n");
	printf("%X\n", color);
	while (i < pos.x + size)
	{
		while (j < pos.y + size)
			draw_pixel_in_image(minimap, j++, i, color);
		j = (int)pos.y;
		i++;
	}
}

void	draw_player(t_game *game, t_vector2 minipos)
{
	int	decimal_x;
	int	decimal_y;

	decimal_x = (int)(game->player.pos.x * 10) % 10;
	decimal_y = (int)(game->player.pos.y * 10) % 10;
	minipos.x += decimal_x;
	minipos.y += decimal_y;
	draw_block(&game->minimap, minipos, 8, 0x00AA00);
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
			draw_pixel_in_image(minimap, i, j, 0x000000);
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
	
	clear_minimap(&game->minimap);
	minipos.x = 0;
	minipos.y = 0;
	player = game->player;
	x_bg = player.pos.x - 5;
	y_bg = player.pos.y - 5;
	x_end = player.pos.x + 5;
	y_end = player.pos.y + 5;
	while (x_bg < x_end)
	{
		y_bg = player.pos.y - 5;
		minipos.y = 0;
		while (y_bg < y_end)
		{
			if (minipos.x == 100 && minipos.y == 100) /* Player position */
			{
				draw_block(&game->minimap, minipos, 20, BLACK);
				draw_player(game, minipos);
			}
			if (in_bounds(x_bg, y_bg, game->map_h, game->map_w)
				&& game->map[x_bg * game->map_w + y_bg] == '1')
				draw_block(&game->minimap, minipos, 20, 0x5555AA);
			else if (in_bounds(x_bg, y_bg, game->map_h, game->map_w)
				&& game->map[x_bg * game->map_w + y_bg] == '0')
				draw_block(&game->minimap, minipos, 20, BLACK);
			if (x_bg < 0 || y_bg < 0 || x_bg >= game->map_h || y_bg >= game->map_w)
				draw_block(&game->minimap, minipos, 20, WHITE);
			y_bg++;
			minipos.y += 20;
		}
		minipos.x += 20;
		x_bg++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->minimap.img, 200, 200);
}
