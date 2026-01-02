/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:00:22 by gada-sil          #+#    #+#             */
/*   Updated: 2026/01/02 15:01:41 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	free_all(char **textures_matrix, char ***textures_array, char *error_msg)
{
	if (textures_matrix)
		free_matrix(textures_matrix);
	free_stack_matrix_array(textures_array);
	if (get_data()->doors)
		free(get_data()->doors);
	return (print_error(error_msg));
}
