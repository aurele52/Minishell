/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokencheck.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:46:49 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/16 16:09:59 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_checkuptwo(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			j = 0;
			while (str[i] && str[i] == c)
			{
				j++;
				i++;
			}
			if (j > 2)
				return (0);
			i--;
		}
		i++;
	}
	return (1);
}

int	ft_checktwo(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			j = 0;
			while (str[i] && str[i] == c)
			{
				j++;
				i++;
			}
			if (j != 2)
				return (0);
			i--;
		}
		i++;
	}
	return (1);
}

int	ft_parenthesischeck(char *str)
{
	int		i;

	i = 1;
	while (str[i] && str[i] != ')')
		i++;
	if (str[i] == '\0')
		return (i);
	else
		return (++i);
}

int	ft_numbercheck(char *str)
{
	if (!ft_checkuptwo(str, '|'))
		return (0);
	if (!ft_checkuptwo(str, '<'))
		return (0);
	if (!ft_checkuptwo(str, '>'))
		return (0);
	while (*str)
	{
		if (*str == '(')
			str = str + ft_parenthesischeck(str);
		else if (*str == ')')
			return (0);
		else
			str++;
	}
	return (1);
}
