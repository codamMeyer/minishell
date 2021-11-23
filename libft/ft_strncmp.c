/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 14:07:56 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/15 12:14:34 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t n)
{
	unsigned char	*s1;
	unsigned char	*s2;
	size_t			i;

	s1 = (unsigned char *)str1;
	s2 = (unsigned char *)str2;
	i = 0;
	if (n == 0)
		return (0);
	while ((s1[i] == s2[i]) && (n > i) && (s1[i] != '\0' && s2[i] != '\0'))
		i++;
	if (i >= n)
		return (0);
	return (s1[i] - s2[i]);
}
