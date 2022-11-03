/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 16:23:35 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/18 22:12:55 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_substr(char const *s, int start, int len, t_pos *garb)
{
	char	*str;

	if (start > ft_strlen(s) || len <= 0)
		return (ft_strdup("", garb));
	while (start + len > ft_strlen(s))
		len--;
	str = ft_malloc(sizeof(char) * (len + 1), garb);
	if (!(str))
		return (0);
	s = start + s;
	str[len] = 0;
	while (len > 0)
	{
		str[len - 1] = s[len - 1];
		len--;
	}
	return (str);
}
