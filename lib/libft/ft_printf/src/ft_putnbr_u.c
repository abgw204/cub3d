/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd_u.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 18:14:04 by gada-sil          #+#    #+#             */
/*   Updated: 2024/10/16 18:14:09 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

int	ft_putnbr_u(unsigned int nb)
{
	char	c;
	char	d;
	int		count_chars;

	count_chars = 0;
	if (nb >= 10)
	{
		count_chars += ft_putnbr_u(nb / 10);
		d = ((nb % 10) + '0');
		write(1, &d, 1);
		count_chars++;
	}
	else
	{
		c = (nb + '0');
		write(1, &c, 1);
		count_chars++;
	}
	return (count_chars);
}
