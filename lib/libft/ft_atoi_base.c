/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artuda-s < artuda-s@student.42porto.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:48:01 by artuda-s          #+#    #+#             */
/*   Updated: 2024/06/23 20:48:24 by artuda-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_base(char *base)
{
	char	c[128];

	if (ft_strlen(base) <= 1)
		return (1);
	ft_bzero(c, 128);
	while (*base)
	{
		if (*base == '+' || *base == '-' || c[(unsigned char)*base])
			return (1);
		c[(unsigned char)*base] = 1;
		base++;
	}
	return (0);
}

static int	base_to_dec(char c, char *base)
{
	int	i;

	i = 0;
	while (*base && c != *base)
	{
		i++;
		base++;
	}
	return (i);
}

int	ft_atoi_base(char *str, char *base)
{
	int	sign;
	int	result;
	int	i;

	if (check_base(base))
		return (0);
	sign = 1;
	result = 0;
	i = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\t' || str[i] == '\v')
		i++;
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (str[i] && ft_strchr(base, ft_tolower(str[i])))
	{
		result = result * ft_strlen(base) + base_to_dec(ft_tolower(str[i]),
				base);
		i++;
	}
	return (result * sign);
}
