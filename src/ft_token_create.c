/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:53:25 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/13 20:00:38 by mgirardo         ###   ########.fr       */
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
		ft_exit(minishell, "malloc error\n");
	ft_lstnew(token, minishell->tokenlist, minishell->garbagecmd);
	if (minishell->tokenlist->start->back == 0)
		ft_exit(minishell, "malloc error\n");
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
		ft_exit(minishell, "malloc error\n");
	ft_lstnew(token, minishell->tokenlist, minishell->garbagecmd);
	if (minishell->tokenlist->start->back == 0)
		ft_exit(minishell, "malloc error\n");
	while (str[i] && str[i] != ' ')
		i++;
	token->tokenstr = ft_substr(str, 0, i, minishell->garbagecmd);
	token->tokentype = WORD;
	return (i);
}

int	ft_tokendoublecote(t_minishell *minishell, char *str)
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
	while (str[i] && str[i] != '"')
		i++;
	if (str[i] == '\0')
		ft_error(minishell, "No matching \"\n");
	else
	{
		token->tokenstr = ft_substr(str, 1, i - 1, minishell->garbagecmd);
		token->tokentype = DOUBLECOTE;
	}
	return (++i);
}

int	ft_tokensinglecote(t_minishell *minishell, char *str)
{
	int		i;
	t_token	*token;

	i = 1;
	token = ft_malloc(sizeof(*token), minishell->garbagecmd);
	if (!token)
		ft_exit(minishell, "malloc error\n");
	ft_lstnew(token, minishell->tokenlist, minishell->garbagecmd);
	if (minishell->tokenlist->start->back == 0)
		ft_exit(minishell, "malloc arror\n");
	while (str[i] && str[i] != '\'')
		i++;
	if (str[i] == '\0')
		ft_error(minishell, "No matching '\n");
	else
	{
		token->tokenstr = ft_substr(str, 1, i - 1, minishell->garbagecmd);
		token->tokentype = SINGLECOTE;
	}
	return (++i);
}

int	ft_tokenparenthesis(t_minishell *minishell, char *str)
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
		while (str[i] && str[i] != ')')
			i++;
		if (str[i] == '\0')
			ft_error(minishell, "NO matching )\n");
		else
		{
			token->tokenstr = ft_substr(str, 1, i - 1, minishell->garbagecmd);
			token->tokentype = PARENTHESIS;
		}
	return (++i);
}

int	ft_tokendash(t_minishell *minishell, char *str)
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
	while (str[i] && str[i] != ' ')
		i++;
	token->tokenstr = ft_substr(str, 0, i, minishell->garbagecmd);
	token->tokentype = DASH;
	return (i);
}

int	ft_tokenlanglebraket(t_minishell *minishell, char *str)
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
	token->tokenstr = ft_substr(str, 0, i, minishell->garbagecmd);
	if (i == 1)
		token->tokentype = IN;
	else
		token->tokentype = HEREDOC;
	return(i);
}

int	ft_tokenranglebraket(t_minishell *minishell, char *str)
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
	token->tokenstr = ft_substr(str, 0, i, minishell->garbagecmd);
	if (i == 1)
		token->tokentype = WRITE;
	else
		token->tokentype = APPEND;
	return (i);
}

int	ft_tokenpipe(t_minishell *minishell, char *str)
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
	while (str[i] && str[i] == '|')
		i++;
	token->tokenstr = ft_substr(str, 0, i, minishell->garbagecmd);
	if (i == 1)
		token->tokentype = PIPE;
	else
		token->tokentype = OR;
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
	token->tokenstr = ft_substr(str, 0, i, minishell->garbagecmd);
	token->tokentype = AND;
	return (i);
}

void	ft_char(t_minishell *minishell, char *str)
{
	while (*str)
	{
		if (*str == ' ')
			str = str + ft_tokenspace(minishell, str);
		else if (*str == '"')
			str = str + ft_tokendoublecote(minishell, str);
		else if (*str == '\'')
			str = str + ft_tokensinglecote(minishell, str);
		else if (*str == '(')
			str = str + ft_tokenparenthesis(minishell, str);
		else if (*str == ')')
		{
			ft_error(minishell, "synthax error\n");
			break;
		}
		else if (*str == '-')
			str = str + ft_tokendash(minishell, str);
		else if (*str == '<')
			str = str + ft_tokenlanglebraket(minishell, str);
		else if (*str == '>')
			str = str + ft_tokenranglebraket(minishell, str);
		else if (*str == '|')
			str = str + ft_tokenpipe(minishell, str);
		else if (*str == '&')
			str = str + ft_tokenand(minishell, str);
		else
			str = str + ft_tokenword(minishell, str);
		/*	token$
			*/
	}
	ft_posprint(minishell->tokenlist, &ft_printtoken);
	ft_posclear(minishell->tokenlist, 0);
	ft_posclear(minishell->garbagecmd, 0);
}

int	ft_checkuptwo(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			j = 0;
			while (str[i] && str[i] == c)
			{
				j++;
				i++;
			}
			if (j > 2 )
				return (0);
			i--;
		}
		i++;
	}
	return (1);
}

int	ft_checktwo(char *str, char c)
{
	int	i;
	int	j;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			j = 0;
			while (str[i] && str[i] == c)
			{
				j++;
				i++;
			}
			if (j != 2 )
				return (0);
			i--;
		}
		i++;
	}
	return (1);
}

int	ft_numbercheck(char *str)
{
	if (!ft_checkuptwo(str, '|'))
		return (0);
	if (!ft_checkuptwo(str, '<'))
		return (0);
	if (!ft_checkuptwo(str, '>'))
		return (0);
	if (!ft_checktwo(str, '&'))
		return (0);
	return (1);
}

void	ft_tokencreate(t_minishell *minishell, char *str)
{
	if (ft_numbercheck(str))
		ft_char(minishell, str);
	else
		ft_error(minishell, "synthax error\n");
}
