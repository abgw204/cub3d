/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 15:12:11 by gada-sil          #+#    #+#             */
/*   Updated: 2024/10/18 17:55:55 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_print_pointer(void *pointer, const char *hex)
{
	unsigned long	ptr;
	char			temp[16];
	int				printed_chars;
	int				i;

	ptr = (unsigned long)pointer;
	printed_chars = 0;
	i = 15;
	if (pointer == NULL)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	while (ptr > 0)
	{
		temp[i--] = hex[ptr % 16];
		ptr /= 16;
	}
	i++;
	printed_chars = 16 - i;
	write(1, "0x", 2);
	write(1, &temp[i], printed_chars);
	return (printed_chars + 2);
}
