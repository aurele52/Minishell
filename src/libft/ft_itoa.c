/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 14:28:16 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/18 15:29:12 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_remp(char *str, int n, int i)
{
	str[i + 1] = 0;
	while (n > 0)
	{
		str[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	return (str);
}

static char	*ft_zero(int i, t_pos *garbage)
{
	char	*str;

	(void)i;
	str = ft_malloc(sizeof(char) * 2, garbage);
	str[0] = '0';
	str[1] = 0;
	return (str);
}

static char	*ft_crea(int n, int i, int moin, t_pos *garbage)
{
	char	*str;

	if (n == 0)
		return (ft_zero(1, garbage));
	str = ft_malloc(sizeof(char) * (i + moin + 1), garbage);
	if (!(str))
		return (0);
	if (moin == 1)
		str[0] = '-';
	return (ft_remp(str, n, i + moin - 1));
}

static char	*ft_min(int i, t_pos *garbage)
{
	char	*str;

	(void)i;
	str = ft_malloc(sizeof(char) * 12, garbage);
	str[0] = '-';
	str[1] = '2';
	str[2] = '1';
	str[3] = '4';
	str[4] = '7';
	str[5] = '4';
	str[6] = '8';
	str[7] = '3';
	str[8] = '6';
	str[9] = '4';
	str[10] = '8';
	str[11] = 0;
	return (str);
}

char	*ft_itoa(int n, t_pos *garbage)
{
	int	nb;
	int	i;
	int	moin;

	i = 0;
	moin = 0;
	if (n == -2147483648)
		return (ft_min(1, garbage));
	if (n < 0)
	{
		n = -n;
		moin = 1;
	}
	nb = n;
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	return (ft_crea(n, i, moin, garbage));
}
