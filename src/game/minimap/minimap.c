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
	int	gap_x;
	int	gap_y;

	decimal_x = game->player.pos.x * 10.0f;
	decimal_y = game->player.pos.y * 10.0f;
	gap_x = (int)decimal_x % 10;
	gap_y = (int)decimal_y % 10;
	printf("x: %d\n", gap_x);
	printf("y: %d\n", gap_y);
	minipos.x += gap_x;
	minipos.y += gap_y;
	draw_block(&game->minimap.minimap_img, minipos, 9, 0x00AA00);
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
	t_iv2	p_pos;

	p_pos.x = 105;
	p_pos.y = 105;
	game->minimap.minimap_img.img = mlx_new_image(game->mlx, 200, 200);
	if (!game->minimap.minimap_img.img)
		return (print_error("Minimap failed to be created!"));
	game->minimap.minimap_img.addr = mlx_get_data_addr(game->minimap.minimap_img.img,
										&game->minimap.minimap_img.bpp,
										&game->minimap.minimap_img.line_len,
										&game->minimap.minimap_img.endian);
	game->minimap.minimap_img.width = 200;
	game->minimap.minimap_img.height = 200;
	//clear_minimap(&game->minimap.minimap_img);
	draw_block(&game->minimap.minimap_img, p_pos, 8, 0x00AA00);
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
	clear_minimap(&mini->minimap_img);
	while (mini->y_bg < mini->y_end)
	{
		while (mini->x_bg < mini->x_end)
		{
			if (!in_bounds(mini->x_bg, mini->y_bg, game->map_w, game->map_h)
				|| game->map[mini->y_bg * game->map_w + mini->x_bg] == 'X')
			{
				draw_block(&mini->minimap_img, mini->pos, 20, BLACK);
				mini->x_bg++;
				mini->pos.x += 20;
				continue ;
			}
			if (mini->pos.x == 100 && mini->pos.y == 100) /* Player position */
			{
				draw_block(&mini->minimap_img, mini->pos, 20, BLACK);
				draw_player(game, mini->pos);
			}
			else if (in_bounds(mini->x_bg, mini->y_bg, game->map_w, game->map_h)
				&& game->map[mini->y_bg * game->map_w + mini->x_bg] == '1')
				draw_block(&mini->minimap_img, mini->pos, 20, 0x5555AA);
			else if (in_bounds(mini->x_bg, mini->y_bg, game->map_w, game->map_h)
				&& (game->map[mini->y_bg * game->map_w + mini->x_bg] == '0'
				|| game->map[mini->y_bg * game->map_w + mini->x_bg] == 'W'))
				draw_block(&mini->minimap_img, mini->pos, 20, 0x00000);
			mini->x_bg++;
			mini->pos.x += 20;
		}
		mini->pos.x = 0;
		mini->x_bg = (int)game->player.pos.x - 5;
		mini->pos.y += 20;
		mini->y_bg++;
	}
	mlx_put_image_to_window(game->mlx, game->win,
						mini->minimap_img.img, 200, 200);
}
