/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:53:26 by artuda-s          #+#    #+#             */
/*   Updated: 2024/04/20 18:27:15 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*pstr;
	size_t	i;

	pstr = (char *)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!pstr)
		return (NULL);
	i = 0;
	while (*str)
	{
		pstr[i] = *str;
		i++;
		str++;
	}
	pstr[i] = 0;
	return (pstr);
}
/* #include <stdio.h>
int	main(void)
{
	char	*str;
	char	*str2;

	str = "lorem ipsum dolor sit amet";
	str2 = ft_strdup(str);
	printf("%s\n", str2);
	return (0);
}
 */