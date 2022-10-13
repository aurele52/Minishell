/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commandcreate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:47:33 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/13 14:59:37 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getpathline(char **env)
{
	int	i;

	i = 0;
	while (env[i] != 0 && (env[i][0] != 'P' || env[i][1] != 'A'
		|| env[i][2] != 'T' || env[i][3] != 'H' || env[i][4] != '='))
		i++;
	if (env[i] == 0)
		return (0);
	return (&env[i][5]);
}

char	**ft_getpath(t_minishell *minishell)
{
	char	*pathline;
	char	**pathtab;

	pathline = ft_getpathline(minishell->actenv);
	pathtab = ft_split(pathline, ':', minishell->garbage);
	return (pathtab);
}

char	*ft_getcmdfile(t_minishell *minishell, char *cmd, t_command *command)
{
	char	**pathtab;
	int		i;

	i = 0;
	pathtab = ft_getpath(minishell, minishell->actenv);
	while (pathtab && pathtab[i] != 0)
	{
		cmdfile = ft_strjoin(ft_strjoin(pathtab[i++],
					"/", minishell->garbage), cmd[0], minishell->garbage);
		if (!cmdfile)
			ft_exit(minishell->garbage, "error malloc");
		if (!access(cmdfile, F_OK))
		{
			if (!access(cmdfile, X_OK))
				return (cmdfile);
			else
				command->error = cmdfile;
		}
	}
}

char	**ft_getcmd(t_minishell *minishell, char *cmd)
{
	return (ft_split(cmd, ' ', minishell->garbage));
}

t_command	*ft_commandcreate(t_minishell *minishell, char *cmd/*cmd de la forme "cat -e"*//*argument suplementaire a voir pour pipe*/)
{
	t_command	*command;

	command = ft_malloc(sizeof(*command), minishell->garbage);
	if (!cmd)
		ft_exit(minishell->garbage, "malloc error");
	command->fdin = 0;
	command->fdout = 1;
	command->cmd = ft_getcmd(minishell, cmd);/*struc *char[2] ou char[0] = "cat" et char[1] = "e" (ou "-e" a voir)*/
	if (!command->cmd)
		ft_exit(minishell->garbage, "error malloc");
	command->cmdfile = ft_getcmdfile(minishell, command);
	return (command);
}





















