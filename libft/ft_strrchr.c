/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 14:08:00 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/15 11:59:38 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	*cursor;
	int		i;
	int		len;

	str = (char *)s;
	cursor = NULL;
	i = 0;
	len = (int)ft_strlen(str);
	if (str[len] == '\0' && c == '\0')
	{
		cursor = &str[len];
		return (cursor);
	}
	while (str[i] != '\0')
	{
		if (str[i] == c)
			cursor = &str[i];
		i++;
	}
	return (cursor);
}
