/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_free_s2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 17:01:51 by gada-sil          #+#    #+#             */
/*   Updated: 2025/10/17 18:07:04 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

char	*join_free_both(char *s1, char *s2)
{
	char	*full;

	full = ft_strjoin(s1, s2);
	if (s2)
		free(s2);
	if (s1)
		free(s1);
	return (full);
}
