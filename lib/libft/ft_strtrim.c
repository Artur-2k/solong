/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s <artuda-s@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 13:42:12 by artuda-s          #+#    #+#             */
/*   Updated: 2024/04/18 13:42:13 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_char_in_str(const char *str, const char c)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

char	*ft_strtrim(const char *s1, const char *set)
{
	char	*nstr;
	size_t	start;
	size_t	end;

	if (!*s1)
		return (ft_strdup(""));
	start = 0;
	end = ft_strlen(s1) - 1;
	while (ft_char_in_str(set, s1[start]))
		start++;
	while (ft_char_in_str(set, s1[end]))
		end--;
	nstr = ft_substr(s1, start, end - start + 1);
	return (nstr);
}

/* #include <stdio.h>

int	main(void)
{
	char * str = "xxxxxxxxxxola mundo!xxxxxxxx";
	char *nstr = ft_strtrim(str, "xyz");
	printf("%s\n", nstr);
	free(nstr);
	return (0);
} */