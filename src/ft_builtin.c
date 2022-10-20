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
	/*	faire test cd : quand cwd deleted ou celui superieur deleted*/
	if (ft_strlen(command->cmd) > 2)
	{
		write(command->ofdout, "minishell: cd: too many arguments\n", ft_strlen("minishell: cd: too many arguments\n"));
		return (1);
	}
	else if (ft_strlen(command->cmd == 2))
	{
		if (chdir(command->cmd[1]) == 0)
		{
			ft_updateenv(minishell);
		}
		else
		{
			write (command->ofdout, "minishell: cd: ", ft_strlen("minishell: cd: "));
			write (command->ofdout, command->cmd[1], ft_strlen(command->cmd[1]));
			write (command->ofdout, ": No such file or directory\n", ft_strlen(": No such file or directory\n"));
			return (1);
		}
	}
	else if (ft_strlen(command->cmd) == 1)
	{
		if (chdir(/*	$HOME if $home existe sinon retour d'erreur
						on peut faire ca car defini comme implementation defined
						in man*/))
		{
			ft_updateenv(minishell);
		}
		else
		{
			write(command->ofdout, "minishell: cd: no home defined\n", ft_strlen("minishell: cd: no home defined\n"));
			return (1);
		}
	}
	return (0);
}

void	ft_export(t_minishell *minishell, t_command *command)
{
	/*	only accept alphanum and underscore to define env variables name
		if no '=' in cmd[1 et +] do nothing
		if '=' and nothing behind put value at '\0'
		for each arg make the check and conversion*/
	/*	prend un env au debut de l'exec, fait ses operations a partir de cet env
		qu'ils sauvegarde dans le nouveau qui sera renvoyer a la fin*/
	/*	may need to remake the parsing for export*/
	if (ft_envvarexist(minishell, command))
		{
			/* replace envact value by new one */
		}
	else
	{
		/* lstnew with command */
	}
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
