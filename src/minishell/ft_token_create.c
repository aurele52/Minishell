/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:53:25 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/29 17:11:51 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isendword(char c)
{
	if (c == ' ' || c == '|' || c == '<' || c == '>')
		return (1);
	if (c == '\'' || c == '"' || c == '$')
		return (1);
	return (0);
}

int	ft_tokennl(t_minishell *minishell)
{
	int		i;
	t_token	*token;

	i = 1;
	token = ft_malloc(sizeof(*token), minishell->garbagecmd);
	if (!token)
		ft_exit(minishell, "malloc error\n");
	ft_lstnew(token, minishell->tokenlist, minishell->garbagecmd);
	if (minishell->tokenlist->start->back == 0)
		ft_exit(minishell, "malloc error\n");
	token->str = ft_strdup("nl", minishell->garbagecmd);
	token->type = NL;
	return (i);
}

int	ft_char2(t_minishell *minishell, char *str)
{
	int	i;

	i = 0;
	if (*str == '<')
		i = ft_tokeninbraket(minishell, str);
	else if (*str == '>')
		i = ft_tokenoutbraket(minishell, str);
	else if (*str == '|')
		i = ft_tokenpipe(minishell, str);
	else if (*str == '$')
		i = ft_tokendollar(minishell, str);
	return (i);
}

int	ft_char(t_minishell *minishell, char *str)
{
	int		i;

	while (*str)
	{
		if (*str == ' ')
			i = ft_tokenspace(minishell, str);
		else if (*str == '"')
			i = ft_tokendoublecote(minishell, str);
		else if (*str == '\'')
			i = ft_tokensinglecote(minishell, str);
		else if (*str == '<' || *str == '>' || *str == '|' || *str == '$')
			i = ft_char2(minishell, str);
		else
			i = ft_tokenword(minishell, str);
		if (i == -1)
			return (-1);
		else
			str = str + i;
	}
	return (0);
}

int	ft_tokencreate(t_minishell *minishell, char *str)
{
	if (ft_strlen(str) == 0 || ft_spacecheck(str) == -1)
		return (-1);
	if (!ft_numbercheck(str))
	{
		ft_error(minishell, "syntax error\n");
		return (-1);
	}
	if (ft_char(minishell, str) == -1)
	{
		ft_error(minishell, "syntax error\n");
		return (-1);
	}
	if (ft_type(minishell->tokenlist->start->back) == SPACES)
		ft_lstdelone(minishell->tokenlist->start->back, 0);
	if (ft_type(minishell->tokenlist->start->back) == PIPE)
	{
		ft_error(minishell, "syntax error\n");
		return (-1);
	}
	ft_tokennl(minishell);
	return (0);
}
