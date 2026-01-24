/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:54:32 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/12 12:07:22 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

/*
 * void draw_gun (draws gun spritesheet with an specific size (GUN_SCALE))
 *
 *  sx: frame x position on spritesheet
 *  sy: frame y position on spritesheet
 *
 *  example:    0, 0 (first frame)
 *              64, 0 (second frame)
 *
 *  src_w: original frame width
 *  src_h: original frame height
 *
 *  x: x on screen
 *  y: y on screen
 *
 *  dst_w: expected width of the final frame on screen
 *  dst_h: expected height of the final frame on screen
 * 
 *  orig_x: corresponding pixel x on the original sprite
 *  orig_y: corresponding pixel y on the original sprite
 * 
 *  example:    Destination (8px):  0 1 2 3 4 5 6 7
 *              Origin  (4px):      0 0 1 1 2 2 3 3
 *
 *  It repeats pixels until the division makes another digit
 *
*/

static void	draw_loop(t_gun g, t_image *screen, int i, int j)
{
	while (++j < g.dst_h)
	{
		i = -1;
		g.sc_y = g.y + j;
		if (g.sc_y < 0 || g.sc_y >= SCREEN_HEIGHT)
			continue ;
		while (++i < g.dst_w)
		{
			g.sc_x = g.x + i;
			if (g.sc_x < 0 || g.sc_x >= SCREEN_WIDTH)
				continue ;
			g.orig_x = (i * g.src_w) / g.dst_w;
			g.orig_y = (j * g.src_h) / g.dst_h;
			g.sheet_offset = (g.sy + g.orig_y) * g.line_len
				+ (g.sx + g.orig_x) * g.bpp;
			g.color = *(unsigned int *)(g.tex->addr + g.sheet_offset);
			if ((g.color & 0x00FFFFFF) != 0)
			{
				g.sc_offset = g.sc_y * g.sc_line_len
					+ g.sc_x * g.sc_bpp;
				*(unsigned int *)(screen->addr + g.sc_offset) = g.color;
			}
		}
	}
}

void	draw_gun(t_game *game, int current, int x, int y)
{
	t_gun	g;

	g.x = x;
	g.y = y;
	g.sx = current * (game->gun.width / 5);
	g.sy = 0;
	g.tex = &game->gun;
	g.src_w = game->gun.width / 5;
	g.src_h = game->gun.height;
	g.dst_w = g.src_w * GUN_SCALE;
	g.dst_h = g.src_h * GUN_SCALE;
	g.bpp = g.tex->bpp >> 3;
	g.line_len = g.tex->line_len;
	g.sc_bpp = game->screen.bpp >> 3;
	g.sc_line_len = game->screen.line_len;
	draw_loop(g, &game->screen, -1, -1);
}

void	draw_sprites(t_game *game)
{
	static int	current = 0;
	static int	timer = 0;

	if (game->keys[6] == '1' && game->is_shooting == false)
	{
		current++;
		game->is_shooting = true;
		game->keys[6] = '0';
	}
	draw_gun(game, current, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50);
	if (game->is_shooting == true)
	{
		timer++;
		if (timer % 2 == 0)
			current++;
		if (current > 5)
		{
			current = 0;
			game->is_shooting = false;
		}
	}
}
