/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgirardo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:25:54 by mgirardo          #+#    #+#             */
/*   Updated: 2022/11/18 18:43:10 by mgirardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_closepipe(t_minishell *minishell)
{
	if (minishell->pipe[0] != 0 && minishell->pipe[0] != 1
		&& minishell->pipe[0] != 2 && minishell->pipe[0] != minishell->pipe[2]
		&& minishell->pipe[0] != minishell->pipe[1])
		close(minishell->pipe[0]);
	minishell->pipe[0] = 0;
	if (minishell->pipe[1] != 0 && minishell->pipe[1] != 1
		&& minishell->pipe[1] != 2 && minishell->pipe[1] != minishell->pipe[2])
		close(minishell->pipe[1]);
	minishell->pipe[1] = 0;
	if (minishell->pipe[2] != 0 && minishell->pipe[2] != 1
		&& minishell->pipe[2] != 2)
		close(minishell->pipe[2]);
	minishell->pipe[2] = 0;
}

void	ft_builtin(t_minishell *minishell, t_command *command)
{
	if (!ft_strcmp(command->cmd[0], "echo"))
		ft_echo(command);
	else if (!ft_strcmp(command->cmd[0], "cd"))
		ft_cd(minishell, command);
	else if (!ft_strcmp(command->cmd[0], "pwd"))
		ft_pwd(minishell, command);
	else if (!ft_strcmp(command->cmd[0], "env"))
		ft_env(minishell, command);
	else if (!ft_strcmp(command->cmd[0], "exit"))
		ft_preexit(minishell, command);
	else if (!ft_strcmp(command->cmd[0], "export"))
		ft_export(minishell, command);
	else if (!ft_strcmp(command->cmd[0], "unset"))
		ft_unset(minishell, command);
	ft_closevaria(2, command->ofdout, command->ofdin);
	ft_closepipe(minishell);
}

int	ft_isbuiltin(t_command *command)
{
	if (command->cmd == 0)
		return (0);
	if (!ft_strcmp(command->cmd[0], "echo"))
		return (1);
	else if (!ft_strcmp(command->cmd[0], "cd"))
		return (1);
	else if (!ft_strcmp(command->cmd[0], "pwd"))
		return (1);
	else if (!ft_strcmp(command->cmd[0], "export"))
		return (1);
	else if (!ft_strcmp(command->cmd[0], "unset"))
		return (1);
	else if (!ft_strcmp(command->cmd[0], "env"))
		return (1);
	else if (!ft_strcmp(command->cmd[0], "exit"))
		return (1);
	return (0);
}
