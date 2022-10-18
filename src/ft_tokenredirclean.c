/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenredirclear.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 22:50:21 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/16 16:49:32 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_type(t_list *list)
{
	t_token	*token;

    token = (t_token *)list->content;
	return (token->type);
}

char	*ft_str(t_list *list)
{
	t_token	*token;

    token = (t_token *)list->content;
	return (token->str);
}

void	ft_errorcmd(t_list *tokenlist)
{
	t_token	*token;

	token = tokenlist->content;
	token->type = ERROR;
	token->str = 0;/*must be change into a pipe a or a and*/
	while (tokenlist->next != tokenlist->pos->start)
		ft_lstdelone(tokenlist->next, 0);
	while (tokenlist->back != tokenlist->pos->start->back || ft_type(tokenlist->back) <= 9)
	{
		if (ft_type(tokenlist->back) == HEREDOC || ft_type(tokenlist->back) == HEREDOCEXT)
			tokenlist = tokenlist->back;
		ft_lstdelone(tokenlist->back, 0);
	}
}

void	ft_expanddollar(t_token *token)
{
		(void)token;
		// a faire
}

void	ft_expanddoublequote(t_token *token)
{
		(void)token;
		// a faire
}

void	ft_tokenjoin(t_minishell *minishell, t_list *tokenlist1, t_list	*tokenlist2)
{
	t_token *token;

	token = (t_token *)tokenlist1->content;
	if (ft_type(tokenlist1) == HEREDOC && (ft_type(tokenlist2) == DOUBLEQUOTE || ft_type(tokenlist2) == SINGLEQUOTE))
		token->type = HEREDOCEXT;
	if (ft_type(tokenlist1) != HEREDOC && ft_type(tokenlist2) == DOLLAR)
		ft_expanddollar(tokenlist2->content);
	if (ft_type(tokenlist1) != HEREDOC && ft_type(tokenlist2) == DOUBLEQUOTE)
		ft_expanddoublequote(tokenlist2->content);
	token->str = ft_strjoin(ft_str(tokenlist1), ft_str(tokenlist2), minishell->garbagecmd);
	if (token->str == 0)
		ft_exit(minishell, "malloc error\n");
	ft_lstdelone(tokenlist2, 0);

}

void	ft_expandforfd(t_minishell *minishell, t_list *tokenlist)
{
	while (ft_type(tokenlist->next) <= 4)
		ft_tokenjoin(minishell, tokenlist, tokenlist->next);
}

void	ft_tokenredirclean(t_minishell *minishell)
{
	t_list	*tokenlist;

	tokenlist = minishell->tokenlist->start;
	while (ft_type(tokenlist) != NL)
	{
		if (ft_type(tokenlist) >= 5 && ft_type(tokenlist) <=8)
		{
			if (ft_type(tokenlist->next) == SPACES)
				ft_lstdelone(tokenlist->next, 0);
			if (ft_type(tokenlist->next) <= 4)
				ft_expandforfd(minishell, tokenlist);
		}
		tokenlist = tokenlist->next;
	}
	if (ft_type(tokenlist) >= 5 && ft_type(tokenlist) <= 8)
		ft_errorcmd(tokenlist);
}
