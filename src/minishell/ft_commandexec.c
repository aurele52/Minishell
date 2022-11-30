/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_commandexec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:35:21 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/30 10:52:47 by mgirardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_whil(t_minishell *minishell, t_command **command, t_list **tokenlist)
{
	int	c;

	if ((*command)->error == 0)
		ft_arg(minishell, *tokenlist);
	ft_setsignalparent();
	c = fork();
	if (c == 0)
	{
		if ((*command)->error != 0)
			ft_exit(minishell, (*command)->error);
		else if ((*command)->cmd[0] == 0)
			ft_exit(minishell, 0);
		else if ((*command)->error == 0)
			ft_executecmd(minishell, (*command));
		else
			ft_exit(minishell, (*command)->error);
	}
	ft_closevaria(2, ft_ofdout(*tokenlist), ft_ofdin(*tokenlist));
	*tokenlist = (*tokenlist)->next->next;
	*command = ft_commandget(*tokenlist);
	if ((*command)->cmd && (*command)->cmd[0] != 0)
		(*command)->file = ft_getcmdfile(minishell, (*command));
	return (c);
}

void	ft_execveerror(t_minishell *mill, int stt, char *err)
{
	if (stt == 139)
	{
		err = ft_strjoin("Minishell: ", err, mill->garbage);
		err = ft_strjoin(err, "\n", mill->garbage);
		if (!err)
			ft_exit(mill, "malloc error\n");
		write(2, err, ft_strlen(err));
	}
	else
		write(2, "\n", 1);
	mill->laststatus = stt;
}

void	ft_else(t_minishell *minishell, t_command *command, t_list *tokenlist)
{
	int			i;
	int			b;
	int			wstatus;
	int			*childid;

	if (command->cmd && command->cmd[0] != 0)
		command->file = ft_getcmdfile(minishell, command);
	i = 0;
	childid = ft_malloc(sizeof(int) * ft_cmdnbr(tokenlist),
			minishell->garbagecmd);
	while (ft_type(tokenlist->back) != NL || i == 0)
		childid[i++] = ft_whil(minishell, &command, &tokenlist);
	b = 0;
	while (b < i)
		waitpid(childid[b++], &wstatus, 0);
	if (WIFEXITED(wstatus) == 1)
		minishell->laststatus = WEXITSTATUS(wstatus);
	else if (WIFEXITED(wstatus) == 0)
		if (WIFSIGNALED(wstatus))
			ft_execveerror(minishell, WTERMSIG(wstatus) + 128, strerror(errno));
}

void	ft_child(t_minishell *minishell, t_list *tokenlist)
{
	t_command	*command;

	if (ft_type(tokenlist) == NL)
		return ;
	command = ft_commandget(tokenlist);
	if (ft_type(tokenlist->next) == NL && ft_isbuiltin(command) == 1)
	{
		ft_openend(ft_commandget(tokenlist));
		ft_builtin(minishell, command);
	}
	else
		ft_else(minishell, command, tokenlist);
	ft_setsignalmain();
}
