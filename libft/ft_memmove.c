/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 14:07:27 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/15 11:52:39 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *str1, const void *str2, size_t n)
{
	char	*dest;
	char	*src;
	int		i;

	dest = (char *)str1;
	src = (char *)str2;
	if (dest > src)
	{
		i = (int)n - 1;
		while (i >= 0)
		{
			dest[i] = src[i];
			i--;
		}
	}
	else if (dest < src)
		ft_memcpy(dest, src, n);
	return (dest);
}
