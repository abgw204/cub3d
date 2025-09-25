/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:00:22 by gada-sil          #+#    #+#             */
/*   Updated: 2025/09/24 18:01:35 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	free_all(char **textures_matrix, char ***textures_array, char *error_msg)
{
	free_stack_matrix_array(textures_array);
	free_matrix(textures_matrix);
	return (print_error(error_msg));
}
