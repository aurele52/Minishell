/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commandexec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:35:21 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/13 14:59:39 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_executesimple(t_minishell *minishell, t_command *command, char *cmd[1], char **cmd, char *error)
{
	if (!access(cmdfile, F_OK) && cmd[0][0] == '.' && cmdfile[1] == '/')
	{
		if (!access(cmdfile, X_OK))
			execve(cmdfile, cmd, minishell->env);
		else
			error = cmdfile;
	}
	if (error)
		ft_exit(minishell->garbage, ft_strjoin("permission denied: ",
				ft_strjoin(error, "\n", minishell->garbage), minishell->garbage));
	ft_exit(minishell->garbage, ft_strjoin("command not found: ",
			ft_strjoin(cmd[0], "\n", minishell->garbage), minishell->garbage));
}

void	ft_execute(t_minishell *minishell, t_command *cmd)
{
	if (!access(command->cmdfile, X_OK))	
		exceve(command->cmdfile, command->cmd, minishell->act);
	ft_executesimple(minishell, command);
}

/* il faut envoyer a ft_execute une struct type command avec a linterrieur le fdin fdout (qu'il faut set sur un pipe si redirection) et la commande en **char avec cmd[0] = "cat" et cmd[1] == "e" (ou "-e" a tester) la struct est creer dans src/ft_commandcreate.c*/
