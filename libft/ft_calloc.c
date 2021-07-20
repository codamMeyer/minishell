/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 14:06:19 by rmeiboom      #+#    #+#                 */
/*   Updated: 2020/11/17 18:57:17 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*voidptr;
	size_t	true_size;

	true_size = count * size;
	voidptr = malloc(true_size);
	if (!voidptr)
		return (NULL);
	else
		ft_bzero(voidptr, true_size);
	return (voidptr);
}
