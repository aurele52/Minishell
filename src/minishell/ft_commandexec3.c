/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commandexec3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:23:31 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/29 18:00:17 by mgirardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_executecmd(t_minishell *minishell, t_command *command)
{
	if (ft_isbuiltin(command) == 1)
	{
		ft_builtin(minishell, command);
		ft_exit(minishell, 0);
	}
	if (command->ofdin != 0)
		dup2(command->ofdin, 0);
	if (command->ofdout != 1)
	{
		dup2(command->ofdout, 1);
		if (command->ofdin != minishell->pipe[0])
			ft_closevaria(1, minishell->pipe[0]);
	}
	ft_closevaria(2, command->ofdin, command->ofdout);
	ft_closepipe(minishell);
	if (command->error == 0)
		execve(command->file, command->cmd, ft_reenv(minishell));
	if (command->error == 0)
		command->error = ft_strjoin(strerror(errno), "\n",
				minishell->garbagecmd);
	ft_exit(minishell, command->error);
}

int	ft_cmdnbr(t_list *tokenlist)
{
	int	i;

	i = 0;
	while (ft_type(tokenlist) != NL)
	{
		if (ft_type(tokenlist) == CMD)
			i++;
		tokenlist = tokenlist->next;
	}
	return (i);
}

int	ft_spacehere(char *str)
{
	int	i;
	int	nbspaces;

	i = -1;
	nbspaces = 0;
	while (str[++i])
	{
		if (str[i] == ' ')
			nbspaces++;
	}
	return (nbspaces);
}

char	**ft_nospaces(t_minishell *minishell, char **str, int size)
{
	char	**cmd;
	int		i;
	char	**tmp;
	int		j;
	int		k;

	cmd = ft_malloc(sizeof(*cmd) * (size + 1), minishell->garbage);
	if (!cmd)
		ft_exit(minishell, "malloc error\n");
	i = -1;
	k = 0;
	while (str[++i])
	{
		if (ft_spacehere(str[i]))
		{
			tmp = ft_split(str[i], ' ', minishell->garbage);
			j = -1;
			while (tmp[++j])
				cmd[k++] = tmp[j];
		}
		else
			cmd[k++] = str[i];
	}
	return (cmd);
}

char	**ft_cmdcheckbfexecve(t_minishell *minishell, char **cmd)
{
	int		i;
	int		nbcmdtoadd;

	i = -1;
	nbcmdtoadd = 0;
	while (cmd[++i])
		nbcmdtoadd += ft_spacehere(cmd[i]);
	if (nbcmdtoadd == 0)
		return (cmd);
	else
	{
		cmd = ft_nospaces(minishell, cmd, nbcmdtoadd + ft_doublstrlen(cmd));
		return (cmd);
	}
}
