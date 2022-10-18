/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgirardo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:25:54 by mgirardo          #+#    #+#             */
/*   Updated: 2022/10/18 14:49:15 by mgirardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_cd(t_minishell *minishell, t_command *command)
{
	
}

void	ft_builtin(t_minishell *minishell, t_command *command)
{
	if (!ft_strcmp(command->cmd[0], "echo"))
		ft_echo(command);
	else if (!ft_strcmp(command->cmd[0], "cd"))
		ft_cd(minishell, command);
	else if (!ft_strcmp(command->cmd[0], "pwd"))
		ft_pwd(minishell, command);
	else if (!ft_strcmp(command->cmd[0], "export"))
		ft_export(minishell, command);	
	else if (!ft_strcmp(command->cmd[0], "unset"))
		ft_unset(minishell, command);
	else if (!ft_strcmp(command->cmd[0], "env"))
		ft_env(minishell, command);
	else if (!ft_strcmp(command->cmd[0], "exit"))
		ft_exit(minishell, command);
	else
		ft_execute(minishell, command); //verif si bonne synthax de ft_execute
}
