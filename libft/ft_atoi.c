/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmeyer <mmeyer@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 14:42:05 by mmeyer        #+#    #+#                 */
/*   Updated: 2021/11/04 15:18:37 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

#define FT_LONG_MAX  9223372036854775807

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
	int				sign;
	int				index;
	long long int	result;

	result = 0;
	sign = 1;
	index = find_first_number(nptr, &sign);
	while (ft_isdigit(nptr[index]))
	{
		if (result == FT_LONG_MAX / 10 && nptr[index] == '7')
			return (255);
		if (result > (FT_LONG_MAX / 10) - 1)
			return (-1);
		result = (nptr[index] - '0') + (result * 10);
		++index;
	}
	return ((int)(result * sign));
}
