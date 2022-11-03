/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbrfd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 20:32:28 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/14 14:10:27 by mgirardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ouijesais(char c, int fd)
{
	write(fd, &c, 1);
}

void	ft_putnbrfd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		n = -n;
		write(fd, "-", 1);
	}
	if (n > 9)
	{
		ft_putnbrfd(n / 10, fd);
		n = n % 10;
	}
	ouijesais(n + '0', fd);
}
