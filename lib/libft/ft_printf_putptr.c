/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 15:27:15 by artuda-s          #+#    #+#             */
/*   Updated: 2024/05/03 16:08:16 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_puthex(unsigned long adr, t_fmtdata *data)
{
	data->n_chars += write(1, "0x", 2);
	if (adr < BASE_16)
		data->n_chars += write(1, &LOW_HEXA[adr], 1);
	else
	{
		ft_putnum_base(adr / BASE_16, data);
		ft_putnum_base(adr % BASE_16, data);
	}
}

void	ft_putptr(void *ptr, t_fmtdata *data)
{
	unsigned long	adr;

	adr = (unsigned long)ptr;
	if (adr == 0)
	{
		data->n_chars += write(1, "(nil)", 5);
		return ;
	}
	ft_puthex(adr, data);
}
