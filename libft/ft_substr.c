/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 14:08:03 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/15 11:50:07 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*str;
	char		*substring;
	size_t		i;

	if (!s)
		return (NULL);
	i = 0;
	str = (char *)s;
	substring = (char *)ft_calloc((len + 1), sizeof(char));
	if (!substring)
		return (NULL);
	while (i < len && str[i] != '\0' && start < ft_strlen(s))
	{
		substring[i] = str[i + start];
		i++;
	}
	return (substring);
}
