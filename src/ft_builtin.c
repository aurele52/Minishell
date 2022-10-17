/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgirardo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:25:54 by mgirardo          #+#    #+#             */
/*   Updated: 2022/10/17 16:25:55 by mgirardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_nonewline(char *str)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	z;

	i = 0;
	j = 0;
	z = 0;
	if (str[i] == '-')
	{
		j = 1;
		i++;
	}
	while (str[i] == 'n')
	{
		z = 1;
		i++;
	}
	if (str[i] == '\0' && z == 1 && j == 1)
		return (0);
	else
		return (1);
}

void	ft_fillofdout(t_command *command, unsigned int i)
{
	while (command->cmd[i])
	{
		write(command->ofdout, command->cmd[i], ft_strlen(command->cmd[i]));
		if (command->cmd[i + 1])
			write(command->ofdout, " ", 1);
		i++;
	}
}

void	ft_echo(t_command *command)
{
	unsigned int	i;

	i = 0;
	if (command->cmd[i + 1])
	{
		i = 1;
		if (ft_nonewline(command->cmd[i]))
		{
			ft_fillofdout(command, 1);
			write(command->ofdout, "\n", 1);
		}
		else
		{
			while (command->cmd[i] && !ft_nonewline(command->cmd[i]))
				i++;
			ft_fillofdout(command, i);
		}
	}
	else
		write(command->ofdout, "\n", 1);
}



/* void	ft_builtin(t_minishell *minishell, t_command *command)
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
   ft_execute(minishell, command); //verif si bonne synthax
   } */
