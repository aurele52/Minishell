/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_create3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 12:43:03 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/16 16:57:45 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tokeninbraket(t_minishell *minishell, char *str)
{
	int		i;
	t_token	*token;

	i = 0;
	token = ft_malloc(sizeof(*token), minishell->garbagecmd);
	if (!token)
		ft_exit(minishell, "malloc error\n");
	ft_lstnew(token, minishell->tokenlist, minishell->garbagecmd);
	if (minishell->tokenlist->start->back == 0)
		ft_exit(minishell, "malloc error\n");
	while (str[i] && str[i] == '<')
		i++;
	token->str = ft_strdup("", minishell->garbagecmd);
	if (i == 1)
		token->type = IN;
	else
		token->type = HEREDOC;
	return (i);
}

int	ft_tokenoutbraket(t_minishell *minishell, char *str)
{
	int		i;
	t_token	*token;

	i = 0;
	token = ft_malloc(sizeof(*token), minishell->garbagecmd);
	if (!token)
		ft_exit(minishell, "malloc error\n");
	ft_lstnew(token, minishell->tokenlist, minishell->garbagecmd);
	if (minishell->tokenlist->start->back == 0)
		ft_exit(minishell, "malloc error\n");
	while (str[i] && str[i] == '>')
		i++;
	token->str = ft_strdup("", minishell->garbagecmd);
	if (i == 1)
		token->type = WRITE;
	else
		token->type = APPEND;
	return (i);
}

int	ft_tokenpipe(t_minishell *minishell, char *str)
{
	int		i;
	t_token	*token;
	t_list	*mem;

	i = 0;
	mem = minishell->tokenlist->start;
	if (*minishell->tokenlist->size == 0 || ft_type(mem->back) == PIPE)
		return (-1);
	if (*minishell->tokenlist->size == 1 && ft_type(mem) == SPACES)
		return (-1);
	if (ft_type(mem->back) == SPACES && ft_type(mem->back->back) == PIPE)
		return (-1);
	token = ft_malloc(sizeof(*token), minishell->garbagecmd);
	ft_lstnew(token, minishell->tokenlist, minishell->garbagecmd);
	if (token == 0 || minishell->tokenlist->start->back == 0)
		ft_exit(minishell, "malloc error\n");
	while (str[i] && str[i] == '|')
		i++;
	token->str = ft_substr(str, 0, i, minishell->garbagecmd);
	if (i == 1)
		token->type = PIPE;
	else
		return (-1);
	return (i);
}

int	ft_tokenand(t_minishell *minishell, char *str)
{
	int		i;
	t_token	*token;

	i = 0;
	token = ft_malloc(sizeof(*token), minishell->garbagecmd);
	if (!token)
		ft_exit(minishell, "malloc error\n");
	ft_lstnew(token, minishell->tokenlist, minishell->garbagecmd);
	if (minishell->tokenlist->start->back == 0)
		ft_exit(minishell, "malloc error\n");
	while (str[i] && str[i] == '&')
		i++;
	token->str = ft_substr(str, 0, i, minishell->garbagecmd);
	token->type = AND;
	return (i);
}

int	ft_tokendollar(t_minishell *minishell, char *str)
{
	int		i;
	t_token	*token;

	i = 1;
	token = ft_malloc(sizeof(*token), minishell->garbagecmd);
	ft_lstnew(token, minishell->tokenlist, minishell->garbagecmd);
	if (!token || minishell->tokenlist->start->back == 0)
		ft_exit(minishell, "malloc error\n");
	if (str[i] <= '9' && str[i] >= '0')
		i++;
	else
	{
		while (str[i] && !ft_isendword(str[i]) && str[i] != '='
			&& str[i] != '+' && str[i] != '/' && str[i] != '"')
			i++;
		if (str[i] == '"' && i == 1)
		{
			token->str = ft_strdup("$$", minishell->garbagecmd);
			token->type = DOLLAR;
			return (i);
		}
	}
	token->str = ft_substr(str, 0, i, minishell->garbagecmd);
	token->type = DOLLAR;
	return (i);
}
