/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:19 by gada-sil          #+#    #+#             */
/*   Updated: 2025/11/05 02:24:34 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

int	in_bounds(int x, int y, int endx, int endy)
{
	return (x >= 0 && y >= 0 && x < endx && y < endy);
}

void	draw_block(t_image *minimap, t_iv2 pos, int size, int color)
{
	int	i;
	int	j;

	i = pos.x;
	j = pos.y;
	while (i < pos.x + size)
	{
		while (j < pos.y + size)
			draw_pixel_in_image(minimap, i, j++, color);
		j = pos.y;
		i++;
	}
}

void	draw_player(t_game *game, t_iv2 minipos)
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

void	clear_minimap(t_image *minimap)
{
	int	i;
	int	j;

	i = -1;
	j = -1;
	while (++i < minimap->height)
	{
		while (++j < minimap->width)
			draw_pixel_in_image(minimap, j, i, 0x005500);
		j = -1;
	}
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
	mini->pos.x = 0;
	mini->pos.y = 0;
	mini->x_bg = (int)game->player.pos.x - 5;
	mini->y_bg = (int)game->player.pos.y - 5;
	mini->x_end = (int)game->player.pos.x + 5;
	mini->y_end = (int)game->player.pos.y + 5;
	clear_minimap(&mini->img);
	while (mini->y_bg < mini->y_end)
	{
		while (mini->x_bg < mini->x_end)
		{
			if (!in_bounds(mini->x_bg, mini->y_bg, game->map_w, game->map_h)
				|| game->map[mini->y_bg * game->map_w + mini->x_bg] == 'X')
			{
				draw_block(&mini->img, mini->pos, 20, WHITE);
				mini->x_bg++;
				mini->pos.x += 20;
				continue ;
			}
			if (mini->pos.x == 100 && mini->pos.y == 100) /* Player position */
			{
				draw_block(&mini->img, mini->pos, 20, BLACK);
				draw_player(game, mini->pos);
			}
			else if (in_bounds(mini->x_bg, mini->y_bg, game->map_w, game->map_h)
				&& game->map[mini->y_bg * game->map_w + mini->x_bg] == '1')
				draw_block(&mini->img, mini->pos, 20, 0x5555AA);
			else if (in_bounds(mini->x_bg, mini->y_bg, game->map_w, game->map_h)
				&& (game->map[mini->y_bg * game->map_w + mini->x_bg] == '0'
				|| game->map[mini->y_bg * game->map_w + mini->x_bg] == 'W'
				|| game->map[mini->y_bg * game->map_w + mini->x_bg] == 'N'))
				draw_block(&mini->img, mini->pos, 20, 0x00000);
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
