/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_posprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:54:06 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/17 14:51:06 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_unsplit(char **tab, char *charset, t_pos *free)
{
	int		i;
	char	*str;

	i = 0;
	str = ft_strdup("", free);
	if (str == 0)
		return (0);
	while (tab[i])
	{
		str = ft_strjoin(str, tab[i], free);
		if (str == 0)
			return (0);
		i++;
		if (tab[i] && charset != 0)
		{
			str = ft_strjoin(str, charset, free);
			if (str == 0)
				return (0);
		}
	}
	return (str);
}

void	ft_printcmd(t_minishell *minishell, t_command *cmd)
{
	char	*str;

	if (cmd->fdin == 0)
		write(2, "fdin = 0\n", 9);
	else
		write(2, cmd->fdin, ft_strlen(cmd->fdin));
	if (cmd->fdout == 0)
		write(2, "fdout = 0\n", 10);
	else
		write(2, cmd->fdout, ft_strlen(cmd->fdout));
	if (cmd->error == 0)
		write(2, "error = 0\n", 10);
	else
	{
		write(2, "error = ", 8);
		write(2, cmd->error, ft_strlen(cmd->error));
		write(2, "\n", 1);
	}
	if (cmd->cmd == 0)
		write(2, "cmd = 0\n", 8);
	else
	{
		str = ft_unsplit(cmd->cmd, "\n", minishell->garbagecmd);
		write(2, "cmd = {\n", 8);
		write(2, str, ft_strlen(str));
		write(2, "\n}\n", 3);
	}
	if (cmd->heredoc == 0)
		write(2, "heredoc = 0\n", 12);
	else
	{
		write(2, "heredoc = ", 10);
		write(2, cmd->heredoc, ft_strlen(cmd->heredoc));
	}
}

void	ft_printtoken(t_minishell *minishell, void *ptr)
{
	t_token	*token;

	token = (t_token *)ptr;
	ft_putnbrfd(token->type, 2);
	write(2, "\n", 1);
	if (token->type == CMD)
		ft_printcmd(minishell, (t_command *)token->str);
	else
		write(2, token->str, ft_strlen(token->str));
	write(2, "\n", 1);
}

void	ft_posprint(t_minishell *minishell, t_pos *pos, void (*fct)(t_minishell *, void *))
{
	t_list	*list;

	if (pos->start != 0)
	{
		list = pos->start;
		while (list != list->pos->start->back)
		{
			printf("------\n");
			(*fct)(minishell, list->content);
			printf("------\n");
			list = list->next;
		}
		printf("------\n");
		(*fct)(minishell, list->content);
		printf("------\n");
	}
}
