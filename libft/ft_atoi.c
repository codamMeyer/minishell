/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmeyer <mmeyer@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 14:42:05 by mmeyer        #+#    #+#                 */
/*   Updated: 2021/11/04 17:00:02 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

#define FT_LONG_MAX  9223372036854775807
#define FT_LONG_MIN  -9223372036854775808

static int	is_space(char a)
{
	if (a == ' ' || a == '\f' || a == '\n')
		return (1);
	if (a == '\r' || a == '\t' || a == '\v')
		return (1);
	return (0);
}

static int	find_first_number(const char *nptr, int *sign)
{
	int	i;

	i = 0;
	while (is_space(nptr[i]))
		++i;
	if (nptr[i] == '-')
	{
		*sign *= -1;
		++i;
	}
	else if (nptr[i] == '+')
		++i;
	return (i);
}

int	ft_atoi(const char *nptr)
{
	const long		long_limits = FT_LONG_MAX / 10;
	int				sign;
	int				index;
	long long int	result;

	result = 0;
	sign = 1;
	index = find_first_number(nptr, &sign);
	while (ft_isdigit(nptr[index]))
	{
		if (result >= long_limits && nptr[index] == '8' && sign == -1)
			return (-2);
		if (result >= long_limits
			&& (nptr[index] >= '7' || nptr[index + 1]))
			return (-1);
		result = (nptr[index] - '0') + (result * 10);
		++index;
	}
	return ((int)(result * sign));
}
