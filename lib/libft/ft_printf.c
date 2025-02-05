/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:37:48 by artuda-s          #+#    #+#             */
/*   Updated: 2024/05/03 16:09:10 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// printf que funcione com %duipxXcs"
// chars will be prommoted to ints
// void *p  -> void *
// xXu		-> unsigned int
// cdi		-> int
// s		-> char *

#include "ft_printf.h"

static void	get_specifier(t_fmtdata *data)
{
	if (data->specifier == '%')
		ft_putchar('%', data);
	else if (data->specifier == 'c')
		ft_putchar((char)va_arg(data->ap, int), data);
	else if (data->specifier == 's')
		ft_putstr(va_arg(data->ap, char *), data);
	else if (ft_strchr("di", data->specifier))
		ft_putnum_base((long long)va_arg(data->ap, int), data);
	else if (ft_strchr("xXu", data->specifier))
	{
		if (data->specifier == 'X')
			ft_putnum_base((long long)va_arg(data->ap, unsigned int), data);
		else
			ft_putnum_base((long long)va_arg(data->ap, unsigned int), data);
	}
	else if (data->specifier == 'p')
		ft_putptr(va_arg(data->ap, void *), data);
}

int	ft_printf(const char *fmt, ...)
{
	t_fmtdata	data;

	if (fmt == NULL || !(*fmt))
		return (-1);
	data.n_chars = 0;
	va_start(data.ap, fmt);
	while (*fmt)
	{
		if (*fmt == '%' && ft_strchr(SPECIFIERS, (char)*(fmt + 1)))
		{
			++fmt;
			data.specifier = *fmt;
			get_specifier(&data);
		}
		else
			data.n_chars += write(1, fmt, 1);
		++fmt;
	}
	va_end(data.ap);
	return (data.n_chars);
}
