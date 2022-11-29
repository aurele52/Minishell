/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commandexec2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 15:21:20 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/17 15:26:06 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_changefdin(t_list *tokenlist, int fd)
{
	t_token		*token;
	t_command	*command;

	token = (t_token *)tokenlist->content;
	command = (t_command *)token->str;
	if (command->ofdin == 0)
		command->ofdin = fd;
}

void	ft_changefdout(t_list *tokenlist, int fd)
{
	t_token		*token;
	t_command	*command;

	token = (t_token *)tokenlist->content;
	command = (t_command *)token->str;
	if (command->ofdout == 1)
		command->ofdout = fd;
}

void	ft_openend(t_command *cmd)
{
	if (cmd->fdin != 0)
		cmd->ofdin = open(cmd->fdin, O_RDONLY, 0644);
	if (cmd->fdout != 0 && cmd->type == 'T')
		cmd->ofdout = open(cmd->fdout, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd->fdout != 0 && cmd->type == 'A')
		cmd->ofdout = open(cmd->fdout, O_WRONLY | O_CREAT | O_APPEND, 0644);
}

void	ft_arg(t_minishell *minishell, t_list *tokenlist)
{
	if (ft_type(tokenlist->back) == PIPE)
	{
		if (!ft_fdin(tokenlist) && ft_type(tokenlist) == CMD)
			ft_changefdin(tokenlist, minishell->pipe[2]);
	}
	if (ft_type(tokenlist->next) == PIPE)
	{
		pipe(minishell->pipe);
		if (!ft_fdout(tokenlist) && ft_type(tokenlist) == CMD)
			ft_changefdout(tokenlist, minishell->pipe[1]);
		minishell->pipe[2] = minishell->pipe[0];
	}
	if (ft_type(tokenlist) == CMD)
		ft_openend(ft_commandget(tokenlist));
}

char	**ft_reenv(t_minishell *minishell)
{
	char	**str;
	int		i;
	t_env	*line;
	t_list	*listact;

	i = 0;
	str = ft_malloc(sizeof(char *) * (*minishell->actenv->size + 1),
			minishell->garbagecmd);
	if (!str)
		ft_exit(minishell, "malloc error\n");
	str[*minishell->actenv->size] = 0;
	listact = minishell->actenv->start;
	while (i < *minishell->actenv->size)
	{
		line = (t_env *)listact->content;
		str[i] = ft_strjoin(line->name, ft_strdup("=", minishell->garbagecmd),
				minishell->garbagecmd);
		str[i] = ft_strjoin(str[i], line->value, minishell->garbagecmd);
		if (!str[i])
			ft_exit(minishell, "malloc error\n");
		listact = listact->next;
		i++;
	}
	return (str);
}
