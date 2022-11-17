/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokencmdclean.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 14:11:29 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/17 18:18:27 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		ft_lstnew(token, minishell->tokenlist, minishell->garbagecmd);
		if (minishell->tokenlist->start->back == 0
			|| minishell->tokenlist->start->back->content == 0)
			ft_exit(minishell, "malloc error\n");
		token->str = str[i];
		token->type = WORD;
		i++;
	}
	tokenlist->pos->start = memstart;
	tokenlist = tokenlist->next;
	ft_lstdelone(tokenlist->back, 0);
}

void	ft_tokenclean3(t_minishell *minishell, t_list *tokenlist)
{
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

void	ft_tokenclean2(t_minishell *minishell, t_list *tokenlist)
{
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
	ft_tokenclean3(minishell, tokenlist);
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
	ft_tokenclean2(minishell, tokenlist);
}
