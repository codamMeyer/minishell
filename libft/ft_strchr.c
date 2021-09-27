/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 14:07:44 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/09/27 22:43:48 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	char		*str;
	char		*cursor;
	size_t		i;
	size_t		len;

	str = (char *)s;
	len = ft_strlen(str);
	i = 0;
	if (c == '\0' && str[len] == c)
	{
		printf("return here\n");
		cursor = &str[len];
		return (cursor);
	}
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			cursor = &str[i];
			return (cursor);
		}
		i++;
	}
	return (NULL);
}
