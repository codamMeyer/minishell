/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstclear.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 14:07:11 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/05/15 11:56:29 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*cursor;
	t_list	*tmp;

	cursor = *lst;
	while (cursor != NULL)
	{
		tmp = cursor;
		cursor = cursor->next;
		del(tmp->content);
		free(tmp);
	}
	*lst = NULL;
}
