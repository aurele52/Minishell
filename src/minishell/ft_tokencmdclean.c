/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokencmdclean.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:11:29 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/15 17:49:26 by mgirardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_resetcommand(t_command *command)
{
	command->fdin = 0;
	command->fdout = 0;
	command->cmd = 0;
	command->error = 0;
	command->ofdout = 1;
	command->ofdin = 0;
}

int	ft_openwrite(t_minishell *minishell, t_command *command, t_token *token)
{
	int	i;

	command->type = 'T';
	i = open(token->str, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (i == -1)
	{
		ft_resetcommand(command);
		command->error = strerror(errno);
		command->error = ft_strjoin(command->error, ft_strdup(" ", minishell->garbagecmd), minishell->garbagecmd);
		command->error = ft_strjoin(command->error, token->str, minishell->garbagecmd);
		command->error = ft_strjoin(command->error, ft_strdup("\n", minishell->garbagecmd), minishell->garbagecmd);
		return (1);
	}
	ft_closevaria(1, i);
	command->fdout = token->str;
	return (0);
}

int	ft_openin(t_minishell *minishell, t_command *command, t_token *token)
{
	int	i;

	i = open(token->str, O_RDONLY, 0777);
	if (i == -1)
	{
		ft_resetcommand(command);
		command->error = strerror(errno);
		command->error = ft_strjoin(command->error, ft_strdup(" ", minishell->garbagecmd), minishell->garbagecmd);
		command->error = ft_strjoin(command->error, token->str, minishell->garbagecmd);
		command->error = ft_strjoin(command->error, ft_strdup("\n", minishell->garbagecmd), minishell->garbagecmd);
		return (1);
	}
	ft_closevaria(1, i);
	command->fdin = token->str;
	return (0);
}

int	ft_openappend(t_minishell *minishell, t_command *command, t_token *token)
{
	int	i;

	command->type = 'A';
	i = open(token->str, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (i == -1)
	{
		ft_resetcommand(command);
		command->error = strerror(errno);
		command->error = ft_strjoin(command->error, ft_strdup(" ", minishell->garbagecmd), minishell->garbagecmd);
		command->error = ft_strjoin(command->error, token->str, minishell->garbagecmd);
		command->error = ft_strjoin(command->error, ft_strdup("\n", minishell->garbagecmd), minishell->garbagecmd);
		return (1);
	}
	ft_closevaria(1, i);
	command->fdout = token->str;
	return (0);
}

int	ft_open(t_minishell *minishell, t_token *token, t_command *command)
{
	if (command->error != 0)
		return (1);
	if (token->type == WRITE)
		return (ft_openwrite(minishell, command, token));
	if (token->type == APPEND)
		return (ft_openappend(minishell, command, token));
	if (token->type == IN)
		return (ft_openin(minishell, command, token));
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
	while (ft_type(tokenlist) < 9)
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
	while (ft_type(tokenlist->next) == IN || ft_type(tokenlist->next) == WRITE || ft_type(tokenlist->next) == APPEND || ft_type(tokenlist->next) == WORD)
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
	while (ft_type(tokenlist) < 9)
	{
		if (ft_type(tokenlist->back) == IN || ft_type(tokenlist->back) == WRITE || ft_type(tokenlist->back) == APPEND || ft_type(tokenlist->back) == WORD)
			ft_lstdelone(tokenlist->back, 0);
		if (ft_type(tokenlist) == IN || ft_type(tokenlist) == WRITE || ft_type(tokenlist) == APPEND)
		{
			if (ft_open(minishell, tokenlist->content, command) == 1)
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

// void	ft_multipletoken(t_minishell *minishell, t_list *tokenlist)
// {
// 	char	*str;
// 	t_list	*memstart;
// 	t_token	*token;

// 	memstart = tokenlist->pos->start;
// 	tokenlist->pos->start = tokenlist->next;
// 	str = ft_str(tokenlist);
// 	token = ft_malloc(sizeof(*token), minishell->garbagecmd);
// 	if (!token)
// 		ft_exit(minishell, "malloc error\n");
// 	ft_lstnew(token, minishell->tokenlist, minishell->garbagecmd);
// 	if (minishell->tokenlist->start->back == 0)
// 		ft_exit(minishell, "malloc error\n");
// 	token->str = str;
// 	token->type = WORD;
// 	tokenlist->pos->start = memstart;
// 	tokenlist = tokenlist->next;
// 	ft_lstdelone(tokenlist->back, 0);
// }



void	ft_multipletoken(t_minishell *minishell, t_list *tokenlist)
{
	char	**str;
	int		i;
	t_list	*memstart;
	t_token	*token;

	memstart = tokenlist->pos->start;
	tokenlist->pos->start = tokenlist->next;
	i = 0;
	str = ft_split(ft_str(tokenlist), ' ', minishell->garbagecmd);
	if (!str)
		ft_exit(minishell, "malloc error\n");
	while (str[i])
	{
		token = ft_malloc(sizeof(*token), minishell->garbagecmd);
		if (!token)
			ft_exit(minishell, "malloc error\n");
		ft_lstnew(token, minishell->tokenlist, minishell->garbagecmd);
		if (minishell->tokenlist->start->back == 0)
			ft_exit(minishell, "malloc error\n");
		token->str = str[i];
		token->type = WORD;
		if (str[i + 1])
		{
			token = ft_malloc(sizeof(*token), minishell->garbagecmd);
			if (!token)
				ft_exit(minishell, "malloc error\n");
			ft_lstnew(token, minishell->tokenlist, minishell->garbagecmd);
			if (minishell->tokenlist->start->back == 0)
				ft_exit(minishell, "malloc error\n");
			token->str = ft_strdup(" ", minishell->garbagecmd);
			token->type = SPACES;
		}
		i++;
	}
	tokenlist->pos->start = memstart;
	tokenlist = tokenlist->next;
	ft_lstdelone(tokenlist->back, 0);
}

void	ft_tokencmdclean(t_minishell *minishell)
{
	t_list	*tokenlist;
	t_token	*token;

	tokenlist = minishell->tokenlist->start;
	while (ft_type(tokenlist) != NL)
	{
		token = tokenlist->content;
		if (token->type == DOUBLEQUOTE)
		{
			token->str = ft_expanddoublequote(minishell, token->str);
			token->type = WORD;
		}
		if (token->type == SINGLEQUOTE)
			token->type = WORD;
		if (token->type == DOLLAR)
		{
			token->str = ft_expanddollar(minishell, token->str + 1);
			ft_multipletoken(minishell, tokenlist);
		}
		tokenlist = tokenlist->next;	
	}
	tokenlist = tokenlist->next;
	char	*temp;
	char	*temp2;
	t_token	*tokenact;

	while (ft_type(tokenlist) != NL)
	{
		if (ft_type(tokenlist) == WORD && ft_type(tokenlist->next) == WORD)
		{
			tokenact = (t_token *)tokenlist->content;
			temp = ft_str(tokenlist);
			temp2 = ft_str(tokenlist->next);
			tokenact->str = ft_strjoin(temp, temp2, minishell->garbagecmd);
			ft_lstdelone(tokenlist->next, 0);
		}
		else
			tokenlist = tokenlist->next;	
	}
	tokenlist = tokenlist->next;	
	while (ft_type(tokenlist) != NL)
	{
		if (ft_type(tokenlist) == SPACES)
		{
			tokenlist = tokenlist->next;
			ft_lstdelone(tokenlist->back, 0);
		}
		else
			tokenlist = tokenlist->next;
	}
	tokenlist = tokenlist->next;

	while (ft_type(tokenlist) != NL)
	{
		tokenlist = ft_commandcreate(minishell, tokenlist);
		if (ft_type(tokenlist) != NL)
			tokenlist = tokenlist->next;
	}
}
