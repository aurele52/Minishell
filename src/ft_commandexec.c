/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commandexec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:35:21 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/25 17:21:28 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (command->ofdout == 1)
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

void	ft_openend(t_command *command)
{
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

char	**ft_reenv(t_minishell *minishell)
{
	char	**str;
	int		i;
	t_env	*line;
	t_list	*listact;

	i = 0;
	str = ft_malloc(sizeof(char *) * (*minishell->actenv->size + 1), minishell->garbagecmd);
	if (!str)
		ft_exit(minishell, "malloc error\n");
	str[*minishell->actenv->size] = 0;
	listact = minishell->actenv->start;
	while (i < *minishell->actenv->size)
	{
		line = (t_env *)listact->content;
		str[i] = ft_strjoin(line->name, line->value, minishell->garbagecmd);
		if (!str[i])
			ft_exit(minishell, "malloc error\n");
		listact = listact->next;
		i++;
	}
	return (str);
}

void	ft_executecmd(t_minishell *minishell, t_command *command)
{
	if (command->ofdin != 0)
	{
//		printf("in = %i\n", command->ofdin);
		dup2(command->ofdin, 0);
	}
	if (command->ofdout != 1)
	{
//		printf("out = %i\n", command->ofdout);
		dup2(command->ofdout, 1);
		if (command->ofdin != minishell->pipe[0])
			ft_closevaria(1, minishell->pipe[0]);
	}
	ft_closevaria(2, command->ofdin, command->ofdout);
	if (command->error == 0)
	{
//		dprintf(2,"1 = %s\n", command->file);
		if (ft_isbuiltin(command) == 1)
			ft_builtin(minishell, command);
		else
			execve(command->file, command->cmd, ft_reenv(minishell)); //env a changer en act env
//		printf("%s \n", strerror(errno));
	}
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

void	ft_child(t_minishell *minishell, t_list *tokenlist)
{
	int			i;
	int			*childid;
	t_command	*command;

	if (ft_type(tokenlist) == NL)
		return ;
	command = ft_commandget(tokenlist);
	if (ft_type(tokenlist->next) == NL && ft_isbuiltin(command) == 1)
		ft_builtin(minishell, command);
	else
	{
		if (command->cmd && command->cmd[0] != 0)
			command->file = ft_getcmdfile(minishell, command);
		i = 0;
		childid = ft_malloc(sizeof(int) *ft_cmdnbr(tokenlist), minishell->garbagecmd);
		while (ft_type(tokenlist->back) != NL || i == 0)
		{
			if (command->error == 0)
				ft_arg(minishell, tokenlist);
			childid[i] = fork();
			if (childid[i] == 0)
			{
				if (command->error == 0)
					ft_executecmd(minishell, command);
				else
				{
					write(2, command->error, ft_strlen(command->error));
					ft_exit(minishell, 0);
				}
			}
			i++;
			ft_closevaria(2, ft_ofdout(tokenlist), ft_ofdin(tokenlist));
			tokenlist = tokenlist->next->next;
			command = ft_commandget(tokenlist);
			if (command->cmd && command->cmd[0] != 0)
				command->file = ft_getcmdfile(minishell, command);
		}
		while (--i >= 0)
			waitpid(childid[i], 0, 0);
	}
}









