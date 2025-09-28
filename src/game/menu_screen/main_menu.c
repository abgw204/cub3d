/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:34 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/24 17:05:35 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	set_buttons_pos(t_image *menu_images)
{
	menu_images[0].x = SCREEN_WIDTH/2 - 300;
	menu_images[0].y = SCREEN_WIDTH/2 - 750;
	menu_images[1].x = SCREEN_WIDTH/2 - 88;
	menu_images[1].y = SCREEN_WIDTH/2 - 420;
	menu_images[2].x = SCREEN_WIDTH/2 - 161;
	menu_images[2].y = SCREEN_WIDTH/2 - 320;
}

void	revert_colors(t_image *image, int color)
{
	int				i;
	unsigned int	*pixel;

	i = 0;
	while (i < image->width * image->height * (image->bpp / 8))
	{
		pixel = (unsigned int *)(image->addr + i);
		if (*pixel == 0xFFFFFF)
			*pixel = color;
		else if (*pixel == 0x00FF00)
			*pixel = color;
		i += image->bpp / 8;
	}
}

int	check_btn_collision(t_image *img, int x, int y)
{
	if (x >= img->x && y >= img->y
		&& x <=  img->x + img->width
		&& y <= img->y + img->height)
		return (1);
	return (0);
}

int	show_main_menu(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win,
						 game->menu_images[0].img,
						 game->menu_images[0].x,
						 game->menu_images[0].y);
	mlx_put_image_to_window(game->mlx,
						 game->win,
						 game->menu_images[1].img,
						 game->menu_images[1].x,
						 game->menu_images[1].y);
	mlx_put_image_to_window(game->mlx,
						 game->win,
						 game->menu_images[2].img,
						 game->menu_images[2].x,
						 game->menu_images[2].y);
	// eventualmente trocar game->state de MAIN_MENU para IN_GAME
	return (0);
}
