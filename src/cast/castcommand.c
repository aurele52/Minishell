/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   castcommand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:43:03 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/02 12:43:15 by audreyer         ###   ########.fr       */
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

t_command	*ft_commandget(t_list *tokenlist)
{
	t_token		*token;
	t_command	*command;

	token = (t_token *)tokenlist->content;
	command = (t_command *)token->str;
	return (command);
}
