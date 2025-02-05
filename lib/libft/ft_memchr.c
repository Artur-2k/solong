/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:04:40 by artuda-s          #+#    #+#             */
/*   Updated: 2024/04/20 21:14:58 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	const char	*pstr;

	pstr = (const char *)str;
	while (n > 0)
	{
		if (*pstr == (char)c)
			return ((void *)pstr);
		pstr++;
		n--;
	}
	return (NULL);
}
