/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 14:07:58 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/15 11:55:28 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strnstrcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i])
	{
		if (s2[i + 1] == '\0')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	length;
	char	*haystack_pos;
	char	*needle_pos;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	length = ft_strlen((char *)needle);
	while (haystack[i] != '\0' && len >= length)
	{
		if (haystack[i] == needle[0])
		{
			haystack_pos = (char *)&haystack[i];
			needle_pos = (char *)&needle[0];
			if (ft_strnstrcmp(haystack_pos, needle_pos) == 1)
				return (haystack_pos);
		}
		i++;
		len--;
	}
	return (NULL);
}
