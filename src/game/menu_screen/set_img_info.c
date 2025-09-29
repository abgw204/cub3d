/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_imgs_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:05:34 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/24 17:05:35 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/cub3d.h"

void	set_menu_images_info(t_image *images)
{
	images[1].addr = mlx_get_data_addr(images[1].img,
		&images[1].bpp,
		&images[1].line_len,
		&images[1].endian);
	images[2].addr = mlx_get_data_addr(images[2].img,
		&images[2].bpp,
		&images[2].line_len,
		&images[2].endian);
	images[3].addr = mlx_get_data_addr(images[3].img,
		&images[3].bpp,
		&images[3].line_len,
		&images[3].endian);
}
