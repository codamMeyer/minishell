/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_dbllst.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/01 18:14:08 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/07/01 18:16:58 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "libft.h"

int	ft_dbllist_size(t_dbllst *head)
{
	t_dbllst	*cursor;
	int			i;

	cursor = head;
	i = 0;
	while (cursor)
	{
		cursor = cursor->next;
		i++;
		if (cursor == head)
			break ;
	}
	return (i);
}

void	ft_addfront_dbl_lst(t_dbllst **head, t_dbllst *new)
{
	new->next = (*head);
	if (!(*head))
	{
		new->next = new;
		new->prev = new;
	}
	if ((*head))
	{
		new->next = *head;
		new->prev = (*head)->prev;
		(*head)->prev = new;
	}
	(*head) = new;
	(*head)->prev->next = new;
}

void	ft_addback_bdl_lst(t_dbllst **head, t_dbllst *new)
{
	if (!(*head))
	{
		new->next = new;
		new->prev = new;
		(*head) = new;
	}
	else
	{
		(*head)->prev->next = new;
		new->next = *head;
		new->prev = (*head)->prev;
		(*head)->prev = new;
	}
}

void	ft_clear_dbllst(t_dbllst **head)
{
	t_dbllst	*cursor;
	t_dbllst	*tmp;

	if (head && *head && (*head)->prev)
	{
		cursor = (*head)->prev;
		while (cursor != *head)
		{
			tmp = cursor;
			cursor = cursor->prev;
			if (tmp)
				free(tmp);
		}
		free(cursor);
		*head = NULL;
	}
}

t_dbllst	*ft_bdllist_new(int data)
{
	t_dbllst	*new_node;

	new_node = (t_dbllst *)malloc(sizeof(t_dbllst));
	if (!new_node)
		return (NULL);
	new_node->num = data;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}
