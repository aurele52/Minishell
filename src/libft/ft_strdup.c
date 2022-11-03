/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 05:43:28 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/14 14:11:00 by mgirardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s, t_pos *garbage)
{
	char	*str;
	int		i;

	i = 0;
	str = ft_malloc((sizeof(char) * ft_strlen((char *)s) + 1), garbage);
	if (!(str))
		return (0);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}
