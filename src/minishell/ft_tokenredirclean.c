/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenredirclean.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 22:50:21 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/17 18:41:48 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_expanddoublequote(t_minishell *minishell, char *str)
{
	char	*temp;
	char	*new;

	new = ft_strdup("", minishell->garbagecmd);
	while (*str)
	{
		temp = ft_recupbeforedollar(minishell, str);
		str = str + ft_strlen(temp);
		new = ft_strjoin(new, temp, minishell->garbagecmd);
		if (*str == '$')
		{
			str++;
			if (*str <= '9' && *str >= '0')
				str++;
			else
				ft_elsedouble(minishell, &str, &temp, &new);
		}
	}
	return (new);
}

int	ft_strhavespace(char *str)
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

void	ft_tokenjoin(t_minishell *minishell, t_list *tokenlist1,
	t_list	*tokenlist2)
{
	t_token	*token1;
	t_token	*token2;

	token1 = (t_token *)tokenlist1->content;
	token2 = (t_token *)tokenlist2->content;
	if (token1->type == HEREDOC && (token2->type == DOUBLEQUOTE
			|| token2->type == SINGLEQUOTE))
		token1->type = HEREDOCEXT;
	if (token1->type != HEREDOC && token1->type != HEREDOCEXT
		&& token2->type == DOLLAR)
	{
		token2->str = ft_expanddollar(minishell, &token2->str[1]);
		if (ft_strhavespace(token2->str) == 1)
		{
			ft_error(minishell, "ambigus redirection\n");
			return ;
		}
	}
	if (token1->type != HEREDOC && token1->type != HEREDOCEXT
		&& token2->type == DOUBLEQUOTE)
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
		if (ft_type(tokenlist) >= 5 && ft_type(tokenlist) <= 8)
		{
			if (ft_type(tokenlist->next) == SPACES)
				ft_lstdelone(tokenlist->next, 0);
			if (ft_type(tokenlist->next) <= 4)
				ft_expandforfd(minishell, tokenlist);
			else
			{
				ft_error(minishell,
					"minishell: syntax error near unexpected token\n");
				return ;
			}
		}
		tokenlist = tokenlist->next;
	}
	if (ft_type(tokenlist) >= 5 && ft_type(tokenlist) <= 8)
		ft_errorcmd(tokenlist);
}
