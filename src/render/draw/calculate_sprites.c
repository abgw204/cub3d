/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_sprites.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 18:54:32 by gada-sil          #+#    #+#             */
/*   Updated: 2025/11/07 08:29:15 by gada-sil         ###   ########.fr       */
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

void	calculate_sprites_size(t_sprite *sp, t_player *player, double *pos_x, double *pos_y)
{
	int	i;

	i = -1;
	while (++i < MAX_PLAYERS - 1)
	{
		sp[i].x = pos_x[i] - player->pos.x;
		sp[i].y = pos_y[i] - player->pos.y;
		sp[i].inv_det = 1.0 / (player->plane.x * player->dir.y
							- player->dir.x * player->plane.y);
		sp[i].transform_x = sp[i].inv_det * (player->dir.y * sp[i].x - player->dir.x * sp[i].y);
		sp[i].transform_y = sp[i].inv_det * (-player->plane.y * sp[i].x + player->plane.x * sp[i].y);
		sp[i].screen_x = (int)((SCREEN_WIDTH / 2) * (1 + sp[i].transform_x / sp[i].transform_y));
		sp[i].height = abs((int)(SCREEN_HEIGHT / sp[i].transform_y));
		sp[i].width = sp[i].height;
		sp[i].start_y = -sp[i].height / 2 + SCREEN_HEIGHT / 2;
		sp[i].end_y = sp[i].height / 2 + SCREEN_HEIGHT / 2;
		sp[i].start_x = -sp[i].width / 2 + sp[i].screen_x;
		sp[i].end_x = sp[i].width / 2 + sp[i].screen_x;
		fix_bondaries(&sp[i]);
	}
}

int	get_further_sprite(t_sprite *sp)
{
	double	max;
	int		i;
	int		found;

	i = -1;
	found = -1;
	max = -1e3;
	while (++i < MAX_PLAYERS - 1)
	{
		if (!sp[i].drawn && sp[i].transform_y > max)
		{
			max = sp[i].transform_y;
			found = i;
		}
	}
	if (sp[found].drawn == true)
		return (-1);
	sp[found].drawn = true;
	return (found);
}

void	calculate_sprites(t_game *game)
{
	static double	pos_x[4] = {5.5, 6.0, 7.5, 9.5};
	static double	pos_y[4] = {10.0, 11.5, 12.0, 10.0};
	int i = -1;
	t_sprite *spr;

	spr = game->sprite;

	calculate_sprites_size(spr, &game->player, pos_x, pos_y);
	while (++i < MAX_PLAYERS - 1)
		spr[i].drawn = false;
	i = -1;
	unsigned int *pixels = (unsigned int *)game->n.addr;
	int tex_pitch = game->n.line_len >> 2;
	int	index = -1;
	t_sprite sp;
	while (++index < MAX_PLAYERS - 1)
	{
		i = get_further_sprite(spr);
		sp = spr[i];
		if (i == -1)
			continue ;
		if (sp.transform_y <= 0.0001)
			continue ;
		for (sp.stripe = sp.start_x; sp.stripe < sp.end_x; sp.stripe++)
    	{
			if (sp.end_x < 0 || sp.start_x >= SCREEN_WIDTH)
				continue;
			sp.tex_x = (int)((sp.stripe - (-sp.width / 2 + sp.screen_x)) * game->n.width / sp.width);
			double tex_step = (double)game->n.height / sp.height;
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
							+ y * game->screen.line_len
							+ sp.stripe * (game->screen.bpp / 8);
						*(unsigned int*)dst = sp.current_color;

					}
				}
			}
		}
	}
}
