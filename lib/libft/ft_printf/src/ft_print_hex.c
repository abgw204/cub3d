/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 13:18:46 by gada-sil          #+#    #+#             */
/*   Updated: 2024/10/16 13:18:48 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_print_hex(unsigned int n, const char *hex)
{
	int		printed_chars;
	char	temp[8];
	int		i;

	printed_chars = 0;
	i = 7;
	if (n == 0)
	{
		write(1, "0", 1);
		return (1);
	}
	while (n > 0)
	{
		temp[i--] = hex[n % 16];
		n /= 16;
	}
	i++;
	printed_chars = 8 - i;
	write(1, &temp[i], printed_chars);
	return (printed_chars);
}
