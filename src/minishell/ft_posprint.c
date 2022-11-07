/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_posprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:54:06 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/30 16:24:30 by audreyer         ###   ########.fr       */
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

void	ft_printenv(t_minishell	*minishell, void *ptr, int fd)
{
	t_env	*env;
	(void)minishell;

	env = (t_env *)ptr;
	if (env->lvalue != 0)
	{
		write(fd, env->name, ft_strlen(env->name));
		write(fd, "=", 1);
		write(fd, env->value, ft_strlen(env->value));
		write(fd, "\n", 1);
	}
}

void	ft_printcmd(t_minishell *minishell, t_command *cmd, int fd)
{
	char	*str;

	(void)fd;
	if (cmd->fdin == 0)
		write(2, "fdin = 0\n", 9);
	else
	{
		write(2, "fdin = ", 8);
		write(2, cmd->fdin, ft_strlen(cmd->fdin));
		write(2, "\n", 1);
	}
	if (cmd->fdout == 0)
		write(2, "fdout = 0\n", 10);
	else
	{
		write(2, "fdout = ", 8);
		write(2, cmd->fdout, ft_strlen(cmd->fdout));
		write(2, "\n", 1);
	}
	if (cmd->ofdout == 0)
		write(2, "ofdout = 0\n", 11);
	else
	{
		write(2, "ofdout = ", 9);
		ft_putnbrfd(cmd->ofdout, 2);
		write(2, "\n", 1);
	}
	if (cmd->ofdin == 0)
		write(2, "ofdin = 0\n", 10);
	else
	{
		write(2, "ofdin = ", 8);
		ft_putnbrfd(cmd->ofdin, 2);
		write(2, "\n", 1);
	}
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
}

void	ft_printtoken(t_minishell *minishell, void *ptr, int fd)
{
	t_token	*token;

	token = (t_token *)ptr;
	ft_putnbrfd(token->type, fd);
	write(fd, "\n", 1);
	if (token->type == CMD)
		ft_printcmd(minishell, (t_command *)token->str, 0);
	else
		write(fd, token->str, ft_strlen(token->str));
	write(fd, "\n", 1);
}

void	ft_posprint(t_minishell *minishell, t_pos *pos, void (*fct)(t_minishell *, void *, int fd), int fd)
{
	t_list	*list;

	if (pos->start != 0)
	{
		list = pos->start;
		while (list != list->pos->start->back)
		{
//			printf("------\n");
			(*fct)(minishell, list->content, fd);
//			printf("------\n");
			list = list->next;
		}
//		printf("------\n");
		(*fct)(minishell, list->content, fd);
//		printf("------\n");
	}
}
