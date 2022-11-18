/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:07:09 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/18 15:22:26 by mgirardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isnum(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i])
	{
		if (str[i] > '9' || str[i] < '0')
			return (0);
		i++;
	}
	return (1);
}

int	ft_demistrcmp(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	if (str1 == 0 || str2 == 0)
		return (-1);
	if (ft_strlen(str1) > ft_strlen(str2))
		return (1);
	while (str1[i])
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}

int	ft_errorstr(char *str)
{
	if (ft_isnum(str))
		return (ft_atoi(str));
	if (ft_demistrcmp("command not found", str) == 0)
		return (127);
	if (ft_demistrcmp("Permission", str) == 0)
		return (126);
	if (ft_demistrcmp("pwd: error retrieving current directory", str) == 0)
		return (1);
	if (ft_demistrcmp("syntax error", str) == 0)
		return (2);
	if (ft_demistrcmp("minishell: syntax error near", str) == 0)
		return (2);
	if (ft_demistrcmp("minishell: exit: too", str) == 0)
		return (1);
	if (ft_demistrcmp("minishell: exit: ", str) == 0)
		return (2);
	if (ft_demistrcmp("minishell: export: ", str) == 0)
		return (1);
	return (0);
}

int	ft_exit(t_minishell *minishell, char *str)
{
	int		i;

	if (str == 0)
			i = minishell->laststatus;
	else
		i = ft_errorstr(str);
	if (str && ft_isnum(str) == 0)
		write(2, str, ft_strlen(str));
	if (minishell->garbagecmd != 0)
		ft_posclear(minishell->garbagecmd, 2);
	if (minishell->garbage != 0)
		ft_posclear(minishell->garbage, 2);
	exit(i);
}
