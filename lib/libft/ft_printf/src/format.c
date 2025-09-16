/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:33:45 by gada-sil          #+#    #+#             */
/*   Updated: 2024/10/15 16:33:47 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

static void	format_format(const char *str, va_list args, int i, int *chars)
{
	if (str[i] == 'd' || str[i] == 'i')
		*chars += ft_putnbr(va_arg(args, int));
	else if (str[i] == 's')
		*chars += ft_putstr(va_arg(args, char *));
	else if (str[i] == 'c')
		*chars += ft_putchar(va_arg(args, int));
	else if (str[i] == 'x')
		*chars += ft_print_hex(va_arg(args, unsigned int),
				"0123456789abcdef");
	else if (str[i] == 'X')
		*chars += ft_print_hex(va_arg(args, unsigned int),
				"0123456789ABCDEF");
	else if (str[i] == 'u')
		*chars += ft_putnbr_u(va_arg(args, unsigned int));
	else if (str[i] == 'p')
		*chars += ft_print_pointer(va_arg(args, void *),
				"0123456789abcdef");
	else if (str[i] == '%')
		*chars += ft_putchar('%');
}

int	format(const char *str, va_list args)
{
	int	i;
	int	printed_chars;

	i = 0;
	printed_chars = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			i++;
			format_format(str, args, i, &printed_chars);
		}
		else
		{
			write(1, &str[i], 1);
			printed_chars++;
		}
		i++;
	}
	return (printed_chars);
}
