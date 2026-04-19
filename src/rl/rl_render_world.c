/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_render_world.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opencode                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19                                #+#    #+#             */
/*   Updated: 2026/04/19                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_rl.h"

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

static void	draw_walls_gpu(t_game *game, const t_rl_tex *t, int screen_w, int screen_h)
{
	int		x;
	double	camera_x;
	double	camera_step;

	camera_x = -1.0;
	camera_step = 2.0 / (double)screen_w;
	for (x = 0; x < screen_w; x++)
	{
		double	ray_dir_x = game->player.dir.x + game->player.plane.x * camera_x;
		double	ray_dir_y = game->player.dir.y + game->player.plane.y * camera_x;
		int		map_x = (int)game->player.pos.x;
		int		map_y = (int)game->player.pos.y;
		double	delta_dist_x = (ray_dir_x == 0.0) ? 1e30 : fabs(1.0 / ray_dir_x);
		double	delta_dist_y = (ray_dir_y == 0.0) ? 1e30 : fabs(1.0 / ray_dir_y);
		double	side_dist_x;
		double	side_dist_y;
		int		step_x;
		int		step_y;
		int		hit = 0;
		int		side = 0;
		double	perp_wall_dist;
		int		line_height;
		int		orig_start;
		int		orig_end;
		int		draw_start;
		int		draw_end;
		double	wall_x;
		int		tex_x;
		Texture2D	tex;

		if (ray_dir_x < 0.0)
		{
			step_x = -1;
			side_dist_x = (game->player.pos.x - (double)map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = ((double)map_x + 1.0 - game->player.pos.x) * delta_dist_x;
		}
		if (ray_dir_y < 0.0)
		{
			step_y = -1;
			side_dist_y = (game->player.pos.y - (double)map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = ((double)map_y + 1.0 - game->player.pos.y) * delta_dist_y;
		}

		while (!hit)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (map_x < 0 || map_y < 0 || map_x >= game->map_w || map_y >= game->map_h)
			{
				hit = 1;
				break;
			}
			if (game->map[map_y * game->map_w + map_x] == '1')
				hit = 1;
		}

		if (side == 0)
			perp_wall_dist = side_dist_x - delta_dist_x;
		else
			perp_wall_dist = side_dist_y - delta_dist_y;
		if (perp_wall_dist < 0.0001)
			perp_wall_dist = 0.0001;

		line_height = (int)((double)screen_h / perp_wall_dist);
		orig_start = -line_height / 2 + screen_h / 2;
		orig_end = line_height / 2 + screen_h / 2;
		draw_start = orig_start;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = orig_end;
		if (draw_end >= screen_h)
			draw_end = screen_h - 1;

		if (side == 0)
		{
			wall_x = game->player.pos.y + perp_wall_dist * ray_dir_y;
			if (ray_dir_x > 0.0)
				tex = t->we;
			else
				tex = t->ea;
		}
		else
		{
			wall_x = game->player.pos.x + perp_wall_dist * ray_dir_x;
			if (ray_dir_y > 0.0)
				tex = t->no;
			else
				tex = t->so;
		}
		wall_x -= floor(wall_x);
		tex_x = (int)(wall_x * (double)tex.width);
		if (tex_x < 0)
			tex_x = 0;
		if (tex_x >= tex.width)
			tex_x = tex.width - 1;
		draw_textured_column(tex, x, orig_start, line_height, draw_start, draw_end, tex_x);
		if (game->z_buffer != NULL)
			game->z_buffer[x] = perp_wall_dist;
		camera_x += camera_step;
	}
}

void	rl_render_scene(t_rl_ctx *ctx)
{
	int				iw;
	int				ih;
	Color			ceil_c;
	Color			floor_c;

	iw = ctx->scene.target.texture.width;
	ih = ctx->scene.target.texture.height;
	ceil_c = rl_color_from_hex_rgb(ctx->game->data->c_color);
	floor_c = rl_color_from_hex_rgb(ctx->game->data->f_color);
	BeginTextureMode(ctx->scene.target);
	DrawRectangle(0, 0, iw, ih / 2, ceil_c);
	DrawRectangle(0, ih / 2, iw, ih - (ih / 2), floor_c);
	draw_walls_gpu(ctx->game, &ctx->assets.walls, iw, ih);
	EndTextureMode();
}
