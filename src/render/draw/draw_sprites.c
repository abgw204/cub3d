/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:54:32 by gada-sil          #+#    #+#             */
/*   Updated: 2025/12/12 15:31:33 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

static void	fix_bondaries(t_sprite *sp)
{
	if (sp->end_x >= SCREEN_WIDTH)
		sp->end_x = SCREEN_WIDTH - 1;
	if (sp->end_y >= SCREEN_HEIGHT)
		sp->end_y = SCREEN_HEIGHT - 1;
	if (sp->start_x < 0)
		sp->start_x = 0;
	if (sp->start_y < 0)
		sp->start_y = 0;
}

void	calculate_sprites_size(t_game *game)
{
	t_players	*p;
	int			i;

	i = -1;
	p = game->players;
	while (++i < MAX_PLAYERS - 1)
	{
		if (p[i].id == game->my_id)
			continue ;
		p[i].sp.x = p[i].x - game->player.pos.x;
		p[i].sp.y = p[i].y - game->player.pos.y;
		p[i].sp.inv_det = 1.0 / (game->player.plane.x * game->player.dir.y
							- game->player.dir.x * game->player.plane.y);
		p[i].sp.transform_x = p[i].sp.inv_det * (game->player.dir.y * p[i].sp.x - game->player.dir.x * p[i].sp.y);
		p[i].sp.transform_y = p[i].sp.inv_det * (-game->player.plane.y * p[i].sp.x + game->player.plane.x * p[i].sp.y);
		p[i].sp.screen_x = (int)((SCREEN_WIDTH / 2) * (1 + p[i].sp.transform_x / p[i].sp.transform_y));
		p[i].sp.height = abs((int)(SCREEN_HEIGHT / p[i].sp.transform_y));
		p[i].sp.width = p[i].sp.height;
		p[i].sp.start_y = -p[i].sp.height / 2 + SCREEN_HEIGHT / 2;
		p[i].sp.end_y = p[i].sp.height / 2 + SCREEN_HEIGHT / 2;
		p[i].sp.start_x = -p[i].sp.width / 2 + p[i].sp.screen_x;
		p[i].sp.end_x = p[i].sp.width / 2 + p[i].sp.screen_x;
		fix_bondaries(&p[i].sp);
	}
}

int	get_further_sprite(t_players *players, int my_id)
{
	double	max;
	int		i;
	int		found;

	i = -1;
	found = -1;
	max = -1e3;
	while (++i < MAX_PLAYERS)
	{
		if (players[i].id == my_id)
			continue ;
		if (!players[i].sp.drawn && players[i].sp.transform_y > max)
		{
			max = players[i].sp.transform_y;
			found = i;
		}
	}
	if (players[found].sp.drawn == true)
		return (-1);
	players[found].sp.drawn = true;
	return (found);
}

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

            // Calcula a posição do pixel dentro do frame
            int orig_x = (i * src_w) / dst_w;
            int orig_y = (j * src_h) / dst_h;

            // Calcular o offset dentro do spritesheet
            int sheet_offset =
                (sy + orig_y) * sheet->line_len +
                (sx + orig_x) * bpp;

            unsigned int color = *(unsigned int *)(sheet->addr + sheet_offset);

            // Verifica a transparência (baseado no canal alpha)
            if ((color & 0x00FFFFFF) != 0) // transparência (alpha == 0)
            {
				
            	// Calcula o offset na tela
            	int screen_offset =
            	    screen_y * game->screen.line_len +
            	    screen_x * screen_bpp;
				
            	// Desenha o pixel no framebuffer
            	*(int *)(game->screen.addr + screen_offset) = color;
			}
        }
    }
}

void	draw_sprites(t_game *game)
{
	int i = -1;
	t_sprite sp;

	calculate_sprites_size(game);
	while (++i < MAX_PLAYERS)
		game->players[i].sp.drawn = false;
	i = -1;
	unsigned int *pixels = (unsigned int *)game->enemy.addr;
	int tex_pitch = game->enemy.line_len >> 2;
	int	index = -1;
	int bpp = game->screen.bpp >> 3;
	int	line_len = game->screen.line_len;
	while (++index < MAX_PLAYERS)
	{
		if (game->players[index].id == game->my_id)
			continue ;
		i = get_further_sprite(game->players, game->my_id);
		sp = game->players[i].sp;
		if (i == -1)
			continue ;
		if (sp.transform_y <= 0.0001)
			continue ;
		for (sp.stripe = sp.start_x; sp.stripe < sp.end_x; sp.stripe++)
    	{
			if (sp.end_x < 0 || sp.start_x >= SCREEN_WIDTH)
				continue;
			sp.tex_x = (int)((sp.stripe - (-sp.width / 2 + sp.screen_x)) * game->enemy.width / sp.width);
			double tex_step = (double)game->enemy.height / sp.height;
    	    if (sp.transform_y > 0 && sp.stripe > 0 && sp.stripe < SCREEN_WIDTH && sp.transform_y < game->z_buffer[sp.stripe])
			{
				double tex_pos = (sp.start_y - (SCREEN_HEIGHT / 2) + sp.height / 2) * tex_step;
				for (int y = sp.start_y; y < sp.end_y; y++) //for every pixel of the current sp.stripe
				{
					sp.tex_y = (int)tex_pos;
					tex_pos += tex_step;
					sp.current_color = pixels[sp.tex_y * tex_pitch + sp.tex_x]; //get current color from the texture
					if ((sp.current_color & 0x00FFFFFF) != 0)
					{
						char *dst = game->screen.addr
							+ y * line_len
							+ sp.stripe * bpp;
						*(unsigned int*)dst = sp.current_color;
					}
				}
			}
		}
	}
	// gun
	static int idx = 0;
	static double	time = 0;
	draw_sprite_scaled(game, &game->gun, idx * (game->gun.width / 5), 0, game->gun.width / 5, game->gun.height, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50, 5);
	time += g_delta_time;
	if (time >= 0.016)
	{
		time = 0;
		idx++;
	}
	if (idx == 5)
		idx = 0;
}
