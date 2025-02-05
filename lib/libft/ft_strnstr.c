/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 17:17:01 by artuda-s          #+#    #+#             */
/*   Updated: 2024/04/16 17:04:48 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	len_little;
	size_t	i;

	len_little = 0;
	while (little[len_little])
		len_little++;
	if (len_little == 0)
		return ((char *)big);
	while (*big && len >= len_little)
	{
		i = 0;
		while (big[i] == little[i])
		{
			if (i == len_little - 1)
				return ((char *)big);
			i++;
		}
		big++;
		len--;
	}
	return (NULL);
}
