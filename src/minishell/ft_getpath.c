/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpath.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgirardo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:50:09 by mgirardo          #+#    #+#             */
/*   Updated: 2022/11/15 13:50:12 by mgirardo         ###   ########.fr       */
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

	pathline = ft_searchinenv(minishell, "PATH");
	pathtab = ft_split(pathline, ':', minishell->garbage);
	return (pathtab);
}

char	*ft_getcmdfile(t_minishell *minishell, t_command *command)
{
	char	**pathtab;
	int		i;
	char	*cmdtmp;
	t_pos	*gar;

	i = 0;
	gar = minishell->garbagecmd;
	if (ft_isbuiltin(command) == 1)
		return (command->cmd[0]);
	pathtab = ft_getpath(minishell);
	if (ft_strlen(command->cmd[0]) <= 2 && command->cmd[0][0] == '.')
	{
		if (ft_strlen(command->cmd[0]) == 1)
		command->error = ft_strdup("'.' must be follow by a command\n", gar);
		if (command->cmd[0][1] == '.')
			command->error = ft_strdup("command not found : ..\n", gar);
		if (command->error != 0)
			return (0);
	}
	while (pathtab && pathtab[i] != 0)
	{
		cmdtmp = ft_strjoin(ft_strjoin(pathtab[i++],
					"/", gar), command->cmd[0], gar);
		if (!cmdtmp)
			ft_exit(minishell, "error malloc\n");
		if (!access(cmdtmp, F_OK))
		{
			if (!access(cmdtmp, X_OK))
				return (cmdtmp);
			else
				command->error = ft_strjoin(ft_strdup("enrro =", gar), cmdtmp, gar);
		}
	}
	if (!access(command->cmd[0], F_OK))
	{
		if (!access(command->cmd[0], X_OK))
			return (command->cmd[0]);
		else
			command->error = ft_strjoin(ft_strdup("enrro =", gar), cmdtmp, gar);
	}
	command->error = ft_strjoin(ft_strdup("command not found : ", gar), command->cmd[0], gar);
	command->error = ft_strjoin(command->error, "\n", gar);
	return (0);
}









