/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gada-sil <gada-sil@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 15:58:30 by gada-sil          #+#    #+#             */
/*   Updated: 2024/10/15 15:58:30 by gada-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int	ft_printf(const char *str, ...);
int	ft_putnbr(int nb);
int	ft_putchar(int c);
int	ft_putstr(const char *s);
int	format(const char *str, va_list args);
int	ft_print_hex(unsigned int n, const char *str);
int	ft_putnbr_u(unsigned int nb);
int	ft_print_pointer(void *pointer, const char *hex);

#endif
