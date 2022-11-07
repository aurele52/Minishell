/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenredirclean.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 22:50:21 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/28 18:45:06 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		lol;

	lol = 0;
	if (!str[0])
	{
		new = ft_strdup("$", minishell->garbagecmd);
		if (!new)
			ft_exit(minishell, "malloc error\n");
		return (new);
	}
	line = minishell->actenv->start;
	while (line != minishell->actenv->start || lol++ == 0)
	{
		if (ft_strcmp(ft_name(line->content), str) == 0)
			return (ft_value(line->content));
		line = line->next;
	}
	new = ft_strdup("", minishell->garbagecmd);
	return (new);
}

char	*ft_expanddollar(t_minishell *minishell, char *str)
{
	char *new;

	if (str[0] == '?')
		new = ft_itoa(minishell->laststatus, minishell->garbagecmd);
	else if (str[0] == '+')
		new = ft_strdup("$+", minishell->garbagecmd);
	else if (str[0] == '=')
		new = ft_strdup("$=", minishell->garbagecmd);
	else
		new = ft_searchinenv(minishell, str);
	if (!new)
		ft_exit(minishell, "malloc error\n");
	return (new);
}

char	*ft_recupbeforedollar(t_minishell *minishell, char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = 0;
	if (!str[i])
		ret = ft_strdup("", minishell->garbagecmd);
	while (str[i] && str[i] != '$')
		i++;
	ret = ft_substr(str, 0, i, minishell->garbagecmd);
	if (!ret)
		ft_exit(minishell, "malloc error\n");
	str = str + i;
	return (ret);
}

char	*ft_expanddoublequote(t_minishell *minishell, char *str)
{
	char	*temp;
	int		i;
	char	*new;

	new = ft_strdup("", minishell->garbagecmd);
	while (*str)
	{
		temp = ft_recupbeforedollar(minishell, str);
		str = str  + ft_strlen(temp);
		new = ft_strjoin(new, temp, minishell->garbagecmd);
		i = 0;
		if (str[i] == '$')
		{
			str++;
			if (str[i] <= '9' && str[i] >= '0')
				str++;
			else
			{
				while (str[i] && str[i] != ' ' && str[i] != '$' && str[i] != '=' && str[i] != '/' && str[i] != '?')
					i++;
				if (i == 0 && str[i] == '?')
					i++;
				temp = ft_expanddollar(minishell, ft_substr(str, 0, i, minishell->garbagecmd));	
				new = ft_strjoin(new, temp, minishell->garbagecmd);
				str = str + i;
			}
		}
	}
	return (new);
}

int		ft_strhavespace(char *str)
{
	int	i;

	while (str && str[i])
	{
		if (str[i] == ' ')
			return (1);
		i++;
	}
	return (0);
}

void	ft_tokenjoin(t_minishell *minishell, t_list *tokenlist1, t_list	*tokenlist2)
{
	t_token *token1;
	t_token	*token2;

	token1 = (t_token *)tokenlist1->content;
	token2 = (t_token *)tokenlist2->content;
	if (token1->type == HEREDOC && (token2->type == DOUBLEQUOTE || token2->type == SINGLEQUOTE))
		token1->type = HEREDOCEXT;
	if (token1->type != HEREDOC && token1->type != HEREDOCEXT && token2->type == DOLLAR)
	{
		token2->str = ft_expanddollar(minishell, &token2->str[1]);
		if (ft_strhavespace(token2->str) == 1)
		{
			ft_error(minishell, "ambigus redirection\n");
			return ;
		}
	}
	if (token1->type != HEREDOC && token1->type != HEREDOCEXT && token2->type == DOUBLEQUOTE)
		token2->str = ft_expanddoublequote(minishell, token2->str);
	token1->str = ft_strjoin(token1->str, token2->str, minishell->garbagecmd);
	if (token1->str == 0)
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
			else
			{
				ft_error(minishell, "minishell: syntax error near unexpected token\n");
				return ;
			}
		}
		tokenlist = tokenlist->next;
	}
	if (ft_type(tokenlist) >= 5 && ft_type(tokenlist) <= 8)
		ft_errorcmd(tokenlist);
}
