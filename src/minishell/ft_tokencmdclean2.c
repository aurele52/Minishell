/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokencmdclean2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:14:39 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/17 18:16:27 by audreyer         ###   ########.fr       */
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
	i = open(token->str, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (i == -1)
	{
		ft_resetcommand(command);
		command->error = strerror(errno);
		command->error = ft_strjoin(command->error,
				ft_strdup(" ", minishell->garbagecmd), minishell->garbagecmd);
		command->error = ft_strjoin(command->error, token->str,
				minishell->garbagecmd);
		command->error = ft_strjoin(command->error, ft_strdup("\n",
					minishell->garbagecmd), minishell->garbagecmd);
		return (1);
	}
	ft_closevaria(1, i);
	command->fdout = token->str;
	return (0);
}

int	ft_openin(t_minishell *minishell, t_command *command, t_token *token)
{
	int	i;

	i = open(token->str, O_RDONLY, 0644);
	if (i == -1)
	{
		ft_resetcommand(command);
		command->error = strerror(errno);
		command->error = ft_strjoin(command->error, ft_strdup(" ",
					minishell->garbagecmd), minishell->garbagecmd);
		command->error = ft_strjoin(command->error, token->str,
				minishell->garbagecmd);
		command->error = ft_strjoin(command->error, ft_strdup("\n",
					minishell->garbagecmd), minishell->garbagecmd);
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
	i = open(token->str, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (i == -1)
	{
		ft_resetcommand(command);
		command->error = strerror(errno);
		command->error = ft_strjoin(command->error, ft_strdup(" ",
					minishell->garbagecmd), minishell->garbagecmd);
		command->error = ft_strjoin(command->error, token->str,
				minishell->garbagecmd);
		command->error = ft_strjoin(command->error, ft_strdup("\n",
					minishell->garbagecmd), minishell->garbagecmd);
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
