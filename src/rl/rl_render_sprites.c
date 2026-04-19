/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_render_sprites.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opencode                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19                                #+#    #+#             */
/*   Updated: 2026/04/19                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_rl.h"

typedef struct s_rl_sprite_ref
{
	int		idx;
	double	depth;
} 	t_rl_sprite_ref;

static void	fix_sprite_boundaries(t_sprite *sp, int screen_w, int screen_h)
{
	if (sp->end_x >= screen_w)
		sp->end_x = screen_w - 1;
	if (sp->end_y >= screen_h)
		sp->end_y = screen_h - 1;
	if (sp->start_x < 0)
		sp->start_x = 0;
	if (sp->start_y < 0)
		sp->start_y = 0;
}

static void	calculate_sprites_size(t_game *game, int screen_w, int screen_h)
{
	t_players	*p;

	p = game->players;
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		if (p[i].id == game->my_id || !p[i].connected)
			continue;
		p[i].sp.x = p[i].x - game->player.pos.x;
		p[i].sp.y = p[i].y - game->player.pos.y;
		p[i].sp.inv_det = 1.0 / (game->player.plane.x * game->player.dir.y
						- game->player.dir.x * game->player.plane.y);
		p[i].sp.transform_x = p[i].sp.inv_det
			* (game->player.dir.y * p[i].sp.x - game->player.dir.x * p[i].sp.y);
		p[i].sp.transform_y = p[i].sp.inv_det
			* (-game->player.plane.y * p[i].sp.x + game->player.plane.x * p[i].sp.y);
		p[i].sp.screen_x = (int)(((double)screen_w / 2.0)
					* (1.0 + p[i].sp.transform_x / p[i].sp.transform_y));
		p[i].sp.height = abs((int)((double)screen_h / p[i].sp.transform_y));
		p[i].sp.width = p[i].sp.height;
		p[i].sp.start_y = -p[i].sp.height / 2 + screen_h / 2;
		p[i].sp.end_y = p[i].sp.height / 2 + screen_h / 2;
		p[i].sp.start_x = -p[i].sp.width / 2 + p[i].sp.screen_x;
		p[i].sp.end_x = p[i].sp.width / 2 + p[i].sp.screen_x;
		fix_sprite_boundaries(&p[i].sp, screen_w, screen_h);
	}
}

static int	cmp_depth_desc(const void *a, const void *b)
{
	const t_rl_sprite_ref	*sa;
	const t_rl_sprite_ref	*sb;

	sa = (const t_rl_sprite_ref *)a;
	sb = (const t_rl_sprite_ref *)b;
	if (sa->depth < sb->depth)
		return (1);
	if (sa->depth > sb->depth)
		return (-1);
	return (0);
}

static void	draw_textured_column(Texture2D tex, int x,
		int orig_start, int line_height, int y0, int y1, int tex_x)
{
	Rectangle	src;
	Rectangle	dst;
	float		tex_y0;
	float		tex_h;

	if (y1 <= y0)
		return;
	tex_y0 = ((float)(y0 - orig_start) / (float)line_height) * (float)tex.height;
	tex_h = ((float)(y1 - y0) / (float)line_height) * (float)tex.height;
	if (tex_y0 < 0.0f)
		tex_y0 = 0.0f;
	if (tex_y0 + tex_h > (float)tex.height)
		tex_h = (float)tex.height - tex_y0;
	src.x = (float)tex_x;
	src.y = tex_y0;
	src.width = 1.0f;
	src.height = tex_h;
	dst.x = (float)x;
	dst.y = (float)y0;
	dst.width = 1.0f;
	dst.height = (float)(y1 - y0);
	DrawTexturePro(tex, src, dst, (Vector2){0.0f, 0.0f}, 0.0f, WHITE);
}

void	rl_render_sprites(t_rl_ctx *ctx)
{
	t_rl_sprite_ref	refs[MAX_PLAYERS];
	int				count;
	int				sw;
	int				sh;
	Texture2D			enemy;
	t_game				*game;

	game = ctx->game;
	enemy = ctx->assets.enemy;
	if (enemy.id == 0 || game->z_buffer == NULL)
		return;
	sw = ctx->scene.target.texture.width;
	sh = ctx->scene.target.texture.height;
	calculate_sprites_size(game, sw, sh);
	count = 0;
	for (int i = 0; i < MAX_PLAYERS; i++)
	{
		if (game->players[i].id == game->my_id || !game->players[i].connected)
			continue;
		if (game->players[i].health <= 0)
			continue;
		if (game->players[i].sp.transform_y <= 0.0001)
			continue;
		refs[count].idx = i;
		refs[count].depth = game->players[i].sp.transform_y;
		count++;
	}
	if (count <= 0)
		return;
	qsort(refs, (size_t)count, sizeof(refs[0]), cmp_depth_desc);
	BeginTextureMode(ctx->scene.target);
	for (int ri = 0; ri < count; ri++)
	{
		t_sprite	sp;
		int		orig_start;
		int		y0;
		int		y1;

		sp = game->players[refs[ri].idx].sp;
		orig_start = -sp.height / 2 + sh / 2;
		y0 = sp.start_y;
		y1 = sp.end_y;
		if (y0 < 0)
			y0 = 0;
		if (y1 >= sh)
			y1 = sh - 1;
		if (sp.end_x < 0 || sp.start_x >= sw)
			continue;
		for (int stripe = sp.start_x; stripe < sp.end_x; stripe++)
		{
			int	tex_x;

			if (stripe < 0 || stripe >= sw)
				continue;
			if (sp.transform_y >= game->z_buffer[stripe])
				continue;
			tex_x = (int)(((double)(stripe - (-sp.width / 2 + sp.screen_x))
					* (double)enemy.width) / (double)sp.width);
			if (tex_x < 0)
				tex_x = 0;
			if (tex_x >= enemy.width)
				tex_x = enemy.width - 1;
			draw_textured_column(enemy, stripe, orig_start, sp.height, y0, y1, tex_x);
		}
	}
	EndTextureMode();
}
