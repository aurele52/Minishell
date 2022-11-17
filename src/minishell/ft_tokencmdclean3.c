/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokencmdclean3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:16:35 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/17 18:18:27 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		tokenlist = tokenlist->next;
	}
	cmd = ft_malloc((sizeof(char *) * (i + 1)), minishell->garbagecmd);
	if (!cmd)
		ft_exit(minishell, "malloc error");
	cmd[i] = 0;
	return (cmd);
}

t_list	*ft_cmdclear(t_list *tokenlist)
{
	while (ft_type(tokenlist->next) == IN
		|| ft_type(tokenlist->next) == WRITE
		|| ft_type(tokenlist->next) == APPEND
		|| ft_type(tokenlist->next) == WORD)
		ft_lstdelone(tokenlist->next, 0);
	return (tokenlist->next);
}

t_list	*ft_whiletoken(t_minishell *minishell, t_list **tokenlist,
	t_command *command, t_token *cmdtoken)
{
	int			i;

	i = 0;
	while (ft_type((*tokenlist)) < 9)
	{
		if (ft_type((*tokenlist)->back) == IN || ft_type((*tokenlist)->back)
			== WRITE || ft_type((*tokenlist)->back) == APPEND
			|| ft_type((*tokenlist)->back) == WORD)
			ft_lstdelone((*tokenlist)->back, 0);
		if (ft_type((*tokenlist)) == IN || ft_type((*tokenlist)) == WRITE
			|| ft_type((*tokenlist)) == APPEND)
		{
			if (ft_open(minishell, (*tokenlist)->content, command) == 1)
			{
				(*tokenlist)->content = cmdtoken;
				return (ft_cmdclear((*tokenlist)));
			}
		}
		else if (ft_type((*tokenlist)) == WORD)
			command->cmd[i++] = ft_str((*tokenlist));
		(*tokenlist) = (*tokenlist)->next;
	}
	return (0);
}

t_list	*ft_commandcreate(t_minishell *minishell, t_list *tokenlist)
{
	t_token		*cmdtoken;
	t_command	*command;
	t_list		*tmp;

	cmdtoken = ft_malloc(sizeof(t_token), minishell->garbagecmd);
	command = ft_commandinit(minishell);
	if (command == 0 || cmdtoken == 0)
		ft_exit(minishell, "error malloc\n");
	cmdtoken->type = CMD;
	cmdtoken->str = (char *)command;
	command->cmd = ft_cmdcharcreate(minishell, tokenlist);
	tmp = ft_whiletoken(minishell, &tokenlist, command, cmdtoken);
	if (tmp)
		return (tmp);
	tokenlist->back->content = cmdtoken;
	return (tokenlist);
}
