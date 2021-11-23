/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 14:07:03 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/15 11:51:28 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*mem_alloc(int n)
{
	int		i;
	int		nbr;
	char	*str;

	i = 0;
	nbr = n;
	if (n < 0)
		nbr *= -1;
	while (nbr > 0)
	{
		nbr /= 10;
		i++;
	}
	i++;
	if (n == -2147483648)
		str = ft_strdup("-2147483648");
	else if (n == 0)
		str = ft_strdup("0");
	else
		str = (char *)malloc(i + 1);
	return (str);
}

static char	*recursive_str(char *str, int nbr, int j)
{
	if (nbr > 0)
	{
		str[j] = nbr % 10 + 48;
		recursive_str(str, nbr / 10, j + 1);
	}
	else
		str[j] = '\0';
	return (str);
}

static void	ft_strrev(char *s)
{
	char	temp;
	int		i;
	int		j;

	i = 0;
	j = ft_strlen(s) - 1;
	while (i < j)
	{
		temp = s[i];
		s[i] = s[j];
		s[j] = temp;
		i++;
		j--;
	}
}

char	*ft_itoa(int n)
{
	int		nbr;
	char	*str;
	int		j;

	nbr = n;
	j = 0;
	str = mem_alloc(n);
	if (!str)
		return (NULL);
	else if (n == -2147483648)
		return (str);
	else if (n == 0)
		return (str);
	if (n < 0)
	{
		nbr *= -1;
		str[j] = '-';
		j++;
	}
	recursive_str(&str[j], nbr, 0);
	ft_strrev(&str[j]);
	return (str);
}
