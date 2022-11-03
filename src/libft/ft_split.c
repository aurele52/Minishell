/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 20:59:57 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/18 00:18:36 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_wcount(char const *s, char c)
{
	int	i;
	int	wcount;

	i = 0;
	wcount = 0;
	while (s[i])
	{
		if ((i == 0 && s[i] != c) || (s[i] != c && s[i - 1] == c))
			wcount++;
		i++;
	}
	return (wcount);
}

static int	ft_wlen(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i] != 0)
		i++;
	return (i);
}

char	**ft_split(char const *s, char c, t_pos *free)
{
	int		a;
	char	**str;

	a = 0;
	if (s == 0)
		return (0);
	str = ft_malloc(sizeof(char *) * (ft_wcount(s, c) + 1), free);
	if (!str)
		return (0);
	str[ft_wcount(s, c)] = 0;
	while (*s != 0)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			str[a] = ft_substr(s, 0, (ft_wlen(s, c)), free);
			if (!str[a])
				return (0);
			a++;
		}
		s = s + ft_wlen(s, c);
	}
	return (str);
}
