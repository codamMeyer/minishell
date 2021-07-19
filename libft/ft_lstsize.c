/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstsize.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 14:07:20 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/15 11:58:44 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*cursor;

	i = 0;
	cursor = lst;
	while (cursor != NULL)
	{
		i++;
		cursor = cursor->next;
	}
	return (i);
}
