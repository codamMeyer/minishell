/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atof.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/05 16:19:16 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/15 13:44:43 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

float	ft_get_float(char *str, float num)
{
	float	i;

	i = 10;
	while (*str && ft_isdigit(*str))
	{
		num = (num * 10) + *str - 48;
		str++;
	}
	if (*str == '.')
	{
		str++;
		while (*str && ft_isdigit(*str))
		{
			num = num + (((*str - 48) / i));
			str++;
			i *= 10;
		}
	}
	return (num);
}

float	ft_atof(char *str)
{
	float	num;
	float	sign;

	sign = 1;
	num = 0;
	if (!str)
		return (0);
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	num = ft_get_float(&(*str), num);
	return (num * sign);
}
