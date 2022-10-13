/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:53:25 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/13 16:29:17 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_tokenspace(t_minishell *minishell, char *str)
{
	int		i;
	t_token	*token;

	i = 0;
	token = ft_malloc(sizeof(*token), minishell->garbagecmd);
	if (!token)
		ft_exit(minishell, "malloc error");
	ft_lstnew(token, minishell->tokenlist, minishell->garbagecmd);
	if (minishell->tokenlist->start->back == 0)
		ft_exit(minishell, "malloc error");
	while (str[i] == ' ')
		i++;
	token->tokenstr = ft_strdup(" ", minishell->garbagecmd);
	token->tokentype = SPACES;
	return (i);
}

int	ft_tokenword(t_minishell *minishell, char *str)
{
	int		i;
	t_token	*token;

	i = 0;
	token = ft_malloc(sizeof(*token), minishell->garbagecmd);
	if (!token)
		ft_exit(minishell, "malloc error");
	ft_lstnew(token, minishell->tokenlist, minishell->garbagecmd);
	if (minishell->tokenlist->start->back == 0)
		ft_exit(minishell, "malloc error");
	while (str[i] && str[i] != ' ')
		i++;
	token->tokenstr = ft_substr(str, 0, i, minishell->garbagecmd);
	token->tokentype = WORD;
	return (i);
}

void	ft_char(t_minishell *minishell, char *str)
{
	while (*str)
	{
		if (*str == ' ')
			str = str + ft_tokenspace(minishell, str);
		else
			str = str + ft_tokenword(minishell, str);
	/* 	tokenword
		tokenspace
		tokentiret
		token'
		token"
		token&&
		token|
		token||
		token()
		token$
		token<
		token<<
		token>
		token>>
		 */
	}
	ft_posprint(minishell->tokenlist, &ft_printtoken);
	ft_posclear(minishell->tokenlist, 0);
	ft_posclear(minishell->garbagecmd, 0);
		printf("arg\n");
}

void	ft_tokencreate(t_minishell *minishell, char *str)
{
	ft_char(minishell, str);
}
