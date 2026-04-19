/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_ui.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: opencode                                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/19                                #+#    #+#             */
/*   Updated: 2026/04/19                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d_rl.h"

bool	rl_ui_draw_death_overlay(int screen_w, int screen_h)
{
	const char	*title;
	const char	*btn;
	int			title_sz;
	int			btn_sz;
	int			tw;
	int			x;
	int			y;
	Rectangle	btn_rect;
	Vector2		m;
	bool		hover;

	DrawRectangle(0, 0, screen_w, screen_h, (Color){ 210, 35, 35, 60 });
	title = "You died";
	btn = "Respawn";
	title_sz = 64;
	btn_sz = 28;
	tw = MeasureText(title, title_sz);
	x = screen_w / 2 - tw / 2;
	y = screen_h / 2 - 150;
	DrawText(title, x, y, title_sz, RAYWHITE);

	btn_rect.width = 260.0f;
	btn_rect.height = 62.0f;
	btn_rect.x = (float)screen_w / 2.0f - btn_rect.width / 2.0f;
	btn_rect.y = (float)screen_h / 2.0f - btn_rect.height / 2.0f + 10.0f;

	m = GetMousePosition();
	hover = CheckCollisionPointRec(m, btn_rect);
	DrawRectangleRounded(btn_rect, 0.25f, 10, (Color){ 22, 22, 26, 235 });
	DrawRectangleLinesEx(btn_rect, 2,
		hover ? (Color){ 245, 245, 255, 220 } : (Color){ 180, 180, 190, 160 });
	{
		int bw = MeasureText(btn, btn_sz);
		DrawText(btn,
			(int)(btn_rect.x + btn_rect.width / 2.0f - (float)bw / 2.0f),
			(int)(btn_rect.y + btn_rect.height / 2.0f - (float)btn_sz / 2.0f),
			btn_sz,
			hover ? RAYWHITE : (Color){ 215, 215, 225, 220 });
	}
	return (hover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT));
}
