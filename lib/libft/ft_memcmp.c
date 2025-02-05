/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:10:34 by artuda-s          #+#    #+#             */
/*   Updated: 2024/04/20 18:07:49 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str1, const void *str2, size_t n)
{
	const char	*pstr1;
	const char	*pstr2;

	pstr1 = str1;
	pstr2 = str2;
	while (n > 0)
	{
		if ((unsigned char)*pstr1 != (unsigned char)*pstr2)
			return ((unsigned char)*pstr1 - (unsigned char)*pstr2);
		pstr1++;
		pstr2++;
		n--;
	}
	return (0);
}
