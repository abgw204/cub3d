/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:54:32 by gada-sil          #+#    #+#             */
/*   Updated: 2025/12/26 14:10:34 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

/*
 * void draw_sprite_scaled (draws a sprite with an specific size (int scale))
 *
 *  sx: frame x position on spritesheet
 *  sy: frame y position on spritesheet
 *
 *  example: 0, 0 (first frame)
 *          64, 0 (second frame)
 *
 *  src_w: original frame width
 *  src_h: original frame height
 *
 *  x: x on screen
 *  y: y on screen
 *
 *  scale: the desired scale to draw the sprite
*/

void draw_sprite_scaled(
    t_game *game,
    t_image *sheet,
    int sx, int sy,     // Posição do frame no spritesheet
    int src_w, int src_h, // Tamanho do frame original
    int x, int y,       // Posição na tela
    float scale)        // Fator de escala
{
    int dst_w = src_w * scale;
    int dst_h = src_h * scale;

    int bpp = sheet->bpp / 8;
    int screen_bpp = game->screen.bpp / 8;
	int line_len = game->screen.line_len;
	int sheet_len = sheet->line_len;

    for (int j = 0; j < dst_h; j++)
    {
        int screen_y = y + j;
        if (screen_y < 0 || screen_y >= SCREEN_HEIGHT)
            continue;
        for (int i = 0; i < dst_w; i++)
        {
            int screen_x = x + i;
            if (screen_x < 0 || screen_x >= SCREEN_WIDTH)
                continue;
            int orig_x = (i * src_w) / dst_w;
            int orig_y = (j * src_h) / dst_h;
            int sheet_offset =
                (sy + orig_y) * sheet_len +
                (sx + orig_x) * bpp;
            unsigned int color = *(unsigned int *)(sheet->addr + sheet_offset);
            if ((color & 0x00FFFFFF) != 0)
            {
            	int screen_offset =
            	    screen_y * line_len +
            	    screen_x * screen_bpp;
            	*(unsigned int *)(game->screen.addr + screen_offset) = color;
			}
        }
    }
}

void	draw_sprites(t_game *game)
{
	static int current = 0;
	static int timer = 0;

	if (game->keys[7] == '1' && game->is_shooting == false)
	{
		current++;
		game->is_shooting = true;
		game->keys[7] = '0';
	}
	// gun
	draw_sprite_scaled(game, &game->gun, current * (game->gun.width / 5), 0, game->gun.width / 5, game->gun.height, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50, 5);
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
