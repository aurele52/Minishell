/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preexit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgirardo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:33:53 by mgirardo          #+#    #+#             */
/*   Updated: 2022/11/23 19:42:32 by mgirardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_alphaarg(t_minishell *minishell, char *str)
{
	char	*error;

	error = ft_strdup(str, minishell->garbage);
	ft_error(minishell, "exit\n");
	error = ft_strjoin("minishell: exit: ", error, minishell->garbage);
	error = ft_strjoin(error, ": numeric argument required\n",
			minishell->garbage);
	ft_exit(minishell, error);
}

void	ft_preexit(t_minishell *minishell, t_command *command)
{
	int		i;

	i = 0;
	if (ft_doublstrlen(command->cmd) == 1)
	{
		i = minishell->laststatus;
		ft_error(minishell, "exit\n");
		ft_exit(minishell, ft_itoa(i, minishell->garbage));
	}
	else if (ft_strlen(*command->cmd) > 1 && !ft_isnum(command->cmd[++i]))
		ft_alphaarg(minishell, command->cmd[i]);
	else if (ft_doublstrlen(command->cmd) > 2)
		ft_error(minishell, "minishell: exit: too many arguments\n");
	else
	{
		i = (ft_atoi(command->cmd[i]) % 256);
		ft_error(minishell, "exit\n");
		ft_exit(minishell, ft_itoa(i, minishell->garbage));
	}
}
