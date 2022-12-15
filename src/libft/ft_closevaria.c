/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_closevaria.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 23:52:12 by audreyer          #+#    #+#             */
/*   Updated: 2022/12/15 17:33:13 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_closevaria(int i, ...)
{
	va_list	param;
	int		fd;

	va_start(param, i);
	while (i > 0)
	{
		fd = va_arg(param, int);
		if (fd != 0 && fd != 2 && fd != 1)
			fd = close(fd);
		i--;
	}
	return (0);
}
