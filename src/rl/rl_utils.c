/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opencode                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19                                #+#    #+#             */
/*   Updated: 2026/04/19                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_rl.h"

#ifndef CUB3D_RL_RENDER_SCALE
# define CUB3D_RL_RENDER_SCALE 0.5f
#endif

int	rl_clampi(int v, int lo, int hi)
{
	if (v < lo)
		return (lo);
	if (v > hi)
		return (hi);
	return (v);
}

RenderTexture2D	rl_create_scene_target(int screen_w, int screen_h)
{
	int	w;
	int	h;

	w = (int)((float)screen_w * CUB3D_RL_RENDER_SCALE);
	h = (int)((float)screen_h * CUB3D_RL_RENDER_SCALE);
	w = rl_clampi(w, 320, screen_w);
	h = rl_clampi(h, 180, screen_h);
	return (LoadRenderTexture(w, h));
}

Color	rl_color_from_hex_rgb(int hex)
{
	Color	c;

	c.r = (unsigned char)((hex >> 16) & 0xFF);
	c.g = (unsigned char)((hex >> 8) & 0xFF);
	c.b = (unsigned char)(hex & 0xFF);
	c.a = 255;
	return (c);
}
