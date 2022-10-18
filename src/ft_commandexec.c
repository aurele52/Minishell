/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commandexec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:35:21 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/18 01:25:58 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_fdout(t_list *tokenlist)
{
	t_token		*token;
	t_command	*command;

	token = (t_token *)tokenlist->content;
	command = (t_command *)token->str;
	if (command->fdout == 0)
		return (0);
	return (1);
}

int	ft_fdin(t_list *tokenlist)
{
	t_token		*token;
	t_command	*command;

	token = (t_token *)tokenlist->content;
	command = (t_command *)token->str;
	if (command->fdin == 0)
		return (0);
	return (1);
}

int	ft_ofdout(t_list *tokenlist)
{
	t_token		*token;
	t_command	*command;

	token = (t_token *)tokenlist->content;
	command = (t_command *)token->str;
	return (command->ofdout);
}

int	ft_ofdin(t_list *tokenlist)
{
	t_token		*token;
	t_command	*command;

	token = (t_token *)tokenlist->content;
	command = (t_command *)token->str;
	return (command->ofdin);
}

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
	if (command->ofdout == 0)
		command->ofdout = fd;
}

t_command *ft_commandget(t_list *tokenlist)
{
	t_token		*token;
	t_command	*command;

	token = (t_token *)tokenlist->content;
	command = (t_command *)token->str;
	return (command);
}

void	ft_heredocend(t_command *command)
{
	(void)command;
}

void	ft_openend(t_command *command)
{
	if (command->heredoc != 0)
	{
		ft_heredocend(command);
	}
	if (command->fdin != 0)
		command->ofdin = open(command->fdin, O_RDONLY, 0777);
	if (command->fdout != 0 && command->type == 'T')
		command->ofdout = open(command->fdout, O_WRONLY | O_CREAT | O_TRUNC , 0777);
	if (command->fdout != 0 && command->type == 'A')
		command->ofdout = open(command->fdout, O_WRONLY | O_CREAT | O_APPEND , 0777);
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

void	ft_executecmd(t_minishell *minishell, t_command *command)
{
	dup2(command->ofdin, 0);
	dup2(command->ofdout, 1);
	ft_closevaria(2, command->ofdin, command->ofdout);
	if (command->error == 0)
		execve(command->cmd[0], command->cmd, minishell->actenv);
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

void	ft_child(t_minishell *minishell, t_list *tokenlist)
{
	int			i;
	int			*childid;
	t_command	*command;

	command = ft_commandget(tokenlist);
	i = 0;
	childid = ft_malloc(sizeof(int) *ft_cmdnbr(tokenlist), minishell->garbagecmd);
	command->cmd[0] = ft_getcmdfile(minishell, command);
	while (ft_type(tokenlist) != NL)
	{
		ft_arg(minishell, tokenlist);
//		childid[i] = fork();
//		if (childid[i] == 0)
			ft_executecmd(minishell, command);
//		else
			ft_closevaria(2, ft_ofdout(tokenlist), ft_ofdin(tokenlist));
		tokenlist = tokenlist->next->next;
	}
	while (i-- > 0)
		waitpid(childid[i], 0, 0);
}









