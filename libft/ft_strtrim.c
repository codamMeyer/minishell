/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 14:08:01 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/15 12:15:39 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set_char(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		else if (i + 1 == (int)ft_strlen(set))
			break ;
		i++;
	}
	return (0);
}

static int	get_front_index(const char *str, const char *set)
{
	int	i;

	i = 0;
	while (is_set_char(str[i], (char *)set) == 1)
		i++;
	return (i);
}

static int	get_back_index(const char *str, const char *set)
{
	int	i;

	i = ft_strlen((char *)str) - 1;
	while (is_set_char(str[i], (char *)set))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start_i;
	int		end_i;
	int		len;
	char	*trimmed;

	if (!s1)
		return (NULL);
	start_i = get_front_index(s1, set);
	end_i = get_back_index(s1, set);
	if (start_i == (int)ft_strlen((char *)s1))
		len = 0;
	else
		len = end_i - start_i + 1;
	trimmed = ft_calloc(len + 1, sizeof(char));
	if (!trimmed)
		return (NULL);
	if (len == 0)
		return (trimmed);
	ft_memcpy(trimmed, &s1[start_i], len);
	return (trimmed);
}
