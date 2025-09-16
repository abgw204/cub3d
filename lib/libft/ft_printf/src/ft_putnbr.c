/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:07:48 by gada-sil          #+#    #+#             */
/*   Updated: 2024/10/15 16:07:48 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putnbr(int nb)
{
	char	d;
	int		count_chars;

	count_chars = 0;
	if (nb == -2147483648)
	{
		count_chars += ft_putstr("-2147483648");
		return (count_chars);
	}
	if (nb < 0)
	{
		count_chars += ft_putchar('-');
		nb = nb * -1;
	}
	if (nb >= 10)
	{
		count_chars += ft_putnbr(nb / 10);
		d = ((nb % 10) + '0');
		count_chars += ft_putchar(d);
	}
	else
		count_chars += ft_putchar(nb + 48);
	return (count_chars);
}
