/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_menu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:34 by gada-sil          #+#    #+#             */
/*   Updated: 2025/10/17 18:00:24 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	set_buttons_pos_menu(t_image *menu_btns)
{
	menu_btns[0].x = SCREEN_WIDTH / 2 - (menu_btns[0].width / 2);
	menu_btns[0].y = 170;
	menu_btns[1].x = menu_btns[0].x + (menu_btns[0].width / 2)
		- menu_btns[1].width / 2;
	menu_btns[1].y = menu_btns[0].y + 280 + (menu_btns[0].height / 2)
		- menu_btns[1].height / 2;
	menu_btns[2].x = menu_btns[1].x + (menu_btns[1].width / 2)
		- menu_btns[2].width / 2;
	menu_btns[2].y = menu_btns[1].y + 90 + (menu_btns[1].height / 2)
		- menu_btns[2].height / 2;
	menu_btns[3].x = menu_btns[2].x + (menu_btns[2].width / 2)
		- menu_btns[3].width / 2;
	menu_btns[3].y = menu_btns[2].y + 90 + (menu_btns[2].height / 2)
		- menu_btns[3].height / 2;
}

void	revert_colors(t_image *image, unsigned int color1, unsigned int color2)
{
	int				i;
	unsigned int	*pixel;
	int				image_size;

	i = 0;
	image_size = image->width * image->height * (image->bpp / 8);
	while (i < image_size)
	{
		pixel = (unsigned int *)(image->addr + i);
		if (*pixel == color1)
			*pixel = color2;
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

int	configure_menu_images(t_game *game)
{
	if (load_menu_images(game))
		return (1);
	set_buttons_pos_menu(game->menu_btns);
	set_menu_images_info(game->menu_btns);
	return (0);
}

int	show_main_menu(t_game *game)
{
	mlx_put_image_to_window(game->mlx, game->win,
						 game->menu_btns[0].img,
						 game->menu_btns[0].x,
						 game->menu_btns[0].y);
	mlx_put_image_to_window(game->mlx,
						 game->win,
						 game->menu_btns[1].img,
						 game->menu_btns[1].x,
						 game->menu_btns[1].y);
	mlx_put_image_to_window(game->mlx,
						 game->win,
						 game->menu_btns[2].img,
						 game->menu_btns[2].x,
						 game->menu_btns[2].y);
	mlx_put_image_to_window(game->mlx,
						 game->win,
						 game->menu_btns[3].img,
						 game->menu_btns[3].x,
						 game->menu_btns[3].y);
	// eventualmente trocar game->state de MAIN_MENU para IN_GAME
	return (0);
}
