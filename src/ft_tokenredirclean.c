/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenredirclean.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 22:50:21 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/18 18:54:47 by audreyer         ###   ########.fr       */
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
	token->str = 0;
	while (tokenlist->next != tokenlist->pos->start)
		ft_lstdelone(tokenlist->next, 0);
	while (tokenlist->back != tokenlist->pos->start->back || ft_type(tokenlist->back) <= 9)
	{
		if (ft_type(tokenlist->back) == HEREDOC || ft_type(tokenlist->back) == HEREDOCEXT)
			tokenlist = tokenlist->back;
		ft_lstdelone(tokenlist->back, 0);
	}
}

char	*ft_searchinenv(t_minishell *minishell, char *str)
{
	t_list	*line;
	char	*new;

	if (!str[0])
	{
		new = ft_strdup("$", minishell->garbagecmd);
		if (!new)
			ft_exit(minishell, "malloc error\n");
		return (new);
	}
	line = minishell->actenv->start;
	while (line != minishell->actenv->start)
	{
		if (ft_strcmp(ft_name(line->content), str) == 0)
			return (ft_value(line->content));
		line = line->next;
	}
	new = ft_strdup("\n", minishell->garbagecmd);
	if (!new)
		ft_exit(minishell, "malloc error\n");
	return (new);
}

void	ft_expanddollar(t_minishell *minishell, char *str)
{
	char *new;

	new = ft_searchinenv(minishell, str);
	return (new);
}

void	ft_expanddoublequote(t_minishell *minishell, char *str)
{
	char	temp;
	int		i;
	char	*new;
	int		j;

	i = 0;
	while (*str)
	{
		while (str[i] && str[i] != '$')
			i++;
		new = ft_substr(str, 0, i - 1, minishell->garbagecmd);
		str = str + i;
		i = 0;
		if (str[i] == '$')
		{
			while (str[i] && str[i] != ' ' && str[i] != '$')
				i++;
			temp = ft_expanddollar(ft_substr(str, 0, i, minishell->garbagecmd));	
			new = ft_strjoin(new, temp, minishell->garbagecmd);
			str = str + i;
			i = 0;
		}
	}
	return (new);
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
