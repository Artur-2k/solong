/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 15:00:18 by artuda-s          #+#    #+#             */
/*   Updated: 2024/04/16 17:04:48 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	char		*pdest;
	const char	*psrc;

	pdest = dest;
	psrc = src;
	if (dest == src)
		return (dest);
	if (dest < src)
	{
		while (len--)
			*pdest++ = *psrc++;
	}
	else
	{
		pdest += len - 1;
		psrc += len - 1;
		while (len--)
			*pdest-- = *psrc--;
	}
	return (dest);
}
