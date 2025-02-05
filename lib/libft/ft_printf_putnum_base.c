/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_putnum_base.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:27:28 by artuda-s          #+#    #+#             */
/*   Updated: 2024/06/23 19:33:32 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_base(t_fmtdata *data)
{
	if (ft_strchr("diu", data->specifier))
	{
		data->lbase = BASE_10;
		data->base_symbols = DECIMAL;
	}
	else if (ft_strchr("xp", data->specifier))
	{
		data->lbase = BASE_16;
		data->base_symbols = LOW_HEXA;
	}
	else
	{
		data->lbase = BASE_16;
		data->base_symbols = UP_HEXA;
	}
}

void	ft_putnum_base(long long num, t_fmtdata *data)
{
	get_base(data);
	if (num < 0 && data->lbase != BASE_16)
	{
		data->n_chars += write(1, "-", 1);
		num = -num;
	}
	if (num < data->lbase)
		data->n_chars += write(1, &data->base_symbols[num], 1);
	else
	{
		ft_putnum_base(num / data->lbase, data);
		ft_putnum_base(num % data->lbase, data);
	}
}
