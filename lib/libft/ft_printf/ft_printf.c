/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:39:46 by gada-sil          #+#    #+#             */
/*   Updated: 2024/10/14 15:39:47 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		printed_chars;

	if (!str)
		return (-1);
	va_start(args, str);
	printed_chars = format(str, args);
	va_end(args);
	return (printed_chars);
}
