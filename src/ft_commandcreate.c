/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commandcreate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:47:33 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/18 00:18:13 by audreyer         ###   ########.fr       */
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

char	*ft_getcmdfile(t_minishell *minishell, t_command *command)
{
	char	**pathtab;
	int		i;
	char	*cmdtmp;

	i = 0;
	pathtab = ft_getpath(minishell);
	while (pathtab && pathtab[i] != 0)
	{
		cmdtmp = ft_strjoin(ft_strjoin(pathtab[i++],
					"/", minishell->garbagecmd), command->cmd[0], minishell->garbagecmd);
		if (!cmdtmp)
			ft_exit(minishell, "error malloc\n");
		if (!access(cmdtmp, F_OK))
		{
			if (!access(cmdtmp, X_OK))
				return (cmdtmp);
			else
				command->error = ft_strjoin(ft_strdup("enro =", minishell->garbagecmd), cmdtmp, minishell->garbagecmd);
		}
	}
	if (!access(command->cmd[0], F_OK))
	{
		if (!access(command->cmd[0], X_OK))
			return (command->cmd[0]);
		else
			command->error = ft_strjoin(ft_strdup("enro =", minishell->garbagecmd), cmdtmp, minishell->garbagecmd);
	}
	return (0);
}









