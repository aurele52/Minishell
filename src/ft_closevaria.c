/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_closevaria.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 23:52:12 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/25 14:33:03 by audreyer         ###   ########.fr       */
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
//			printf("%i\n", fd);
		if (fd != 0 && fd != 2 && fd != 1)
		{
			fd = close(fd);
			if (fd == -1)
				write(2, "n2p", 3);
		}
		i--;
	}
	return (0);
}
