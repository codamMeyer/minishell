/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 14:07:42 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/15 11:59:20 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static int	get_delimiter_count(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (s[0] != c && s[0] != '\0')
		count++;
	while (s[i] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

static void	free_split(char **split_array, int count)
{
	while (count >= 0)
	{
		free(split_array[count]);
		count--;
	}
	free(split_array);
}

static char	**split_loop(char **splitstr, const char *s, int del_i, char c)
{
	int	i;
	int	j;

	i = 0;
	while (i < del_i)
	{
		j = 0;
		while (s[j] == c)
			s++;
		while (s[j] != c && s[j] != '\0')
			j++;
		splitstr[i] = (char *)malloc(j + 1 * sizeof(char));
		if (splitstr[i] == NULL)
		{
			free_split(splitstr, i - 1);
			return (NULL);
		}
		ft_memcpy(splitstr[i], s, j);
		splitstr[i][j] = '\0';
		s = &s[j];
		i++;
	}
	if (del_i != 0)
		splitstr[i] = NULL;
	return (splitstr);
}

char	**ft_split(char const *s, char c)
{
	char	**split_strs;
	int		del_count;

	if (s == NULL)
		return (NULL);
	del_count = get_delimiter_count(s, c);
	split_strs = (char **)malloc((del_count + 1) * sizeof(char *));
	if (split_strs == NULL)
		return (NULL);
	else if (del_count == 0 || s[0] == '\0')
	{
		split_strs[0] = NULL;
		return (split_strs);
	}
	split_strs = split_loop(split_strs, s, del_count, c);
	return (split_strs);
}
