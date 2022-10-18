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

void	ft_updateenv(t_minishell *minishell)
{
	/*	lstdelone(OLDPWD)
		lstnew(OLDPWD = PWD)
		creer buff[PATH_MAX]
		getcwd(buff, PATH_MAX)
		lstdelone(PWD)
		lstnew(PWD = buff)*/
}

int	ft_cd(t_minishell *minishell, t_command *command)
{
	if (ft_strlen(command->cmd) > 2)
	{
		write(2, "bash: cd: too many arguments")
		return (1);
	}
	else if (ft_strlen(command->cmd == 2))
	{
		if (chdir(command->cmd[1]) == 0)
		{
			ft_updateenv(minishell);
		}
	}
	else if (ft_strlen(comman->cmd) == 1)
	{
		if (chdir(/*	$HOME if $home existe sinon retour d'erreur
						on peut faire ca car defini comme implementation defined
						in man*/))
		{
			ft_updateenv(minishell);
		}
		else
		{
			write(2, "bash: cd: no home defined")
			return (1);
		}
	}
	return (0);
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
		ft_executecmd(minishell, command); //verif si bonne synthax de ft_execute
}
