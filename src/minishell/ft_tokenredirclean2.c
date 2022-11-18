/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenredirclean2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 18:39:13 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/18 15:17:48 by mgirardo         ###   ########.fr       */
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
	while (tokenlist->back != tokenlist->pos->start->back
		|| ft_type(tokenlist->back) <= 9)
	{
		if (ft_type(tokenlist->back) == HEREDOC
			|| ft_type(tokenlist->back) == HEREDOCEXT)
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
	char	*new;

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

int	ft_elsedouble(t_minishell *minishell, char **str, char **temp, char **new)
{
	int	i;

	i = 0;
	while ((*str)[i] && (*str)[i] != ' ' && (*str)[i] != '$'
		&& (*str)[i] != '=' && (*str)[i] != '/' && (*str)[i] != '?')
		i++;
	if (i == 0 && (*str)[i] == '?')
		i++;
	(*temp) = ft_expanddollar(minishell, ft_substr((*str),
				0, i, minishell->garbagecmd));
	*new = ft_strjoin(*new, *temp, minishell->garbagecmd);
	*str = (*str) + i;
	return (i);
}
