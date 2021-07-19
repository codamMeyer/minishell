/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putendl_fd.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rmeiboom <rmeiboom@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/14 14:07:34 by rmeiboom      #+#    #+#                 */
/*   Updated: 2021/06/30 16:03:50 by rmeiboom      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *str, int fd)
{
	if (str != NULL)
	{
		write(fd, str, ft_strlen(str));
		ft_putchar_fd('\n', fd);
	}
}
