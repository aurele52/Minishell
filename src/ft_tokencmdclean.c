/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokencmdclean.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:11:29 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/18 01:19:02 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	while (ft_strcmp(str, token->str) != 0)
//	{
//		write(0, ">", 1);
//		str = ft_readline(">", minishell->garbagecmd);
//		if (str == 0)
//			ft_exit(minishell, "readline error\n");
//		if (ft_strcmp(str, token->str) != 0)
//			write(fd, str, ft_strlen(str));
//	}
	
void	ft_heredoc(t_minishell *minishell, t_token *token, t_command *command)
{
	int		fd;
	char	*fdin;

	fdin = ft_strdup("", minishell->garbagecmd);	
	fdin = ft_strjoin(fdin, "\"", minishell->garbagecmd);
	fdin = ft_strjoin(fdin, token->str, minishell->garbagecmd);
	fdin = ft_strjoin(fdin, "\"", minishell->garbagecmd);
	command->fdin = 0;
	if (command->heredoc == 0)
		command->heredoc = fdin;
	else
		command->heredoc = ft_strjoin(command->heredoc, fdin, minishell->garbagecmd);
	if (!command->heredoc)
		ft_exit(minishell, "malloc error\n");
	fd = open("heredoc_tmp", O_CREAT | O_TRUNC | O_RDWR, 0777);
	close(fd);
}

void	ft_resetcommand(t_command *command)
{
	command->fdin = 0;
	command->fdout = 0;
	command->cmd = 0;
	command->error = 0;
	command->ofdout = 1;
	command->ofdin = 0;
	command->heredoc = 0;
}

int	ft_open(t_token *token, t_command *command)
{
	int	i;

	i = 0;
	if (command->error != 0)
		return (1);
	if (token->type == WRITE)
	{
		command->type = 'T';
		i = open(token->str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		if (i == -1)
		{
			ft_resetcommand(command);
			command->error = strerror(errno);
			return (1);
		}
		close(i);
		command->fdout = token->str;
	}
	else if (token->type == APPEND)
	{
		command->type = 'A';
		i = open(token->str, O_WRONLY | O_CREAT | O_APPEND, 0777);
		if (i == -1)
		{
			ft_resetcommand(command);
			command->error = strerror(errno);
			return (1);
		}
		close(i);
		command->fdout = token->str;
	}
	else if (token->type == IN)
	{
		i = open(token->str, O_RDONLY, 0777);
		if (i == -1)
		{
			ft_resetcommand(command);
			command->error = strerror(errno);
			return (1);
		}
		close(i);
		command->fdin = token->str;
	}
	return (0);
}

t_command	*ft_commandinit(t_minishell *minishell)
{
	t_command	*command;

	command = ft_malloc(sizeof(*command), minishell->garbagecmd);
	if (!command)
		ft_exit(minishell, "malloc error");
	command->fdin = 0;
	command->fdout = 0;
	command->cmd = 0;
	command->heredoc = 0;
	command->error = 0;
	command->ofdout = 1;
	command->ofdin = 0;
	return (command);
}

char	**ft_cmdcharcreate(t_minishell *minishell, t_list *tokenlist)
{
	int		i;
	char	**cmd;

	i = 0;
	while (ft_type(tokenlist) < 9 || ft_type(tokenlist) == HEREDOCEXT)
	{
		if (ft_type(tokenlist) == WORD)
			i++;
		tokenlist =tokenlist->next;
	}
	cmd = ft_malloc((sizeof(char *) * (i + 1)), minishell->garbagecmd);
	if (!cmd)
		ft_exit(minishell, "malloc error");
	cmd[i] = 0;
	return (cmd);
}

t_list	*ft_cmdclear(t_list *tokenlist)
{
	while (ft_type(tokenlist->next) == HEREDOC || ft_type(tokenlist->next) == HEREDOCEXT || ft_type(tokenlist->next) == IN || ft_type(tokenlist->next) == WRITE || ft_type(tokenlist->next) == APPEND || ft_type(tokenlist->next) == WORD)
		ft_lstdelone(tokenlist->next, 0);
	return (tokenlist->next);
}
t_list	*ft_commandcreate(t_minishell *minishell, t_list *tokenlist)
{
	t_token		*cmdtoken;
	t_command	*command;
	int			i;

	i = 0;
	cmdtoken = ft_malloc(sizeof(t_token), minishell->garbagecmd);
	command = ft_commandinit(minishell);
	if (command == 0 || cmdtoken == 0)
		ft_exit(minishell, "error malloc\n");
	cmdtoken->type = CMD;
	cmdtoken->str = (char *)command;
	command->cmd = ft_cmdcharcreate(minishell, tokenlist);
	while (ft_type(tokenlist) < 9 || ft_type(tokenlist) == HEREDOCEXT)
	{
		if (ft_type(tokenlist->back) == HEREDOC || ft_type(tokenlist->back) == HEREDOCEXT || ft_type(tokenlist->back) == IN || ft_type(tokenlist->back) == WRITE || ft_type(tokenlist->back) == APPEND || ft_type(tokenlist->back) == WORD)
			ft_lstdelone(tokenlist->back, 0);
		if (ft_type(tokenlist) == HEREDOC || ft_type(tokenlist) == HEREDOCEXT)
			ft_heredoc(minishell, (t_token *)tokenlist->content, command);
		else if (ft_type(tokenlist) == IN || ft_type(tokenlist) == WRITE || ft_type(tokenlist) == APPEND)
		{
			if (ft_open(tokenlist->content, command) == 1)
			{
				tokenlist->content = cmdtoken;
				return (ft_cmdclear(tokenlist));
			}
		}
		else if (ft_type(tokenlist) == WORD)
			command->cmd[i++] = ft_str(tokenlist);
		tokenlist = tokenlist->next;
	}
	tokenlist->back->content = cmdtoken;
	return (tokenlist);
}

void	ft_expandsimplequote(t_token *token)
{
	int		i;
	char	*str;

	i = 0;
	str = token->str;
	str++;
	while (str[i])
		i++;
	str[i - 1] = 0;
	token->str = str;
}

void	ft_tokencmdclean(t_minishell *minishell)
{
	t_list	*tokenlist;
	int	i;

	i = 0;
	tokenlist = minishell->tokenlist->start;
	while (ft_type(tokenlist) != NL)
	{
		if (ft_type(tokenlist) == DOUBLEQUOTE)
			ft_expanddoublequote((t_token *)tokenlist->content);
		if (ft_type(tokenlist) == SINGLEQUOTE)
			ft_expandsimplequote((t_token *)tokenlist->content);
		if (ft_type(tokenlist) == DOLLAR)
			ft_expanddollar((t_token *)tokenlist->content);
		if (ft_type(tokenlist->next) == SPACES)
			ft_lstdelone(tokenlist->next, 0);
		tokenlist = tokenlist->next;	
	}
	tokenlist = tokenlist->next;
	while (ft_type(tokenlist) != NL && i++ < 5)
	{
		tokenlist = ft_commandcreate(minishell, tokenlist);
		ft_posprint(minishell, minishell->tokenlist, &ft_printtoken);
		if (ft_type(tokenlist) != NL)
			tokenlist = tokenlist->next;
	}
}

