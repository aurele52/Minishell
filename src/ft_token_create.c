/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_create.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:53:25 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/27 13:29:18 by audreyer         ###   ########.fr       */
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
	token->str = ft_strdup(" ", minishell->garbagecmd);
	token->type = SPACES;
	return (i);
}

int	ft_isendword(char c)
{
	if (c == ' ' || c == '|' || c == '&' || c == '<' || c == '>')
		return (1);
	if (c == '\'' || c == '"' || c == '$')
		return (1);
	return (0);
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
	while (str[i] && !ft_isendword(str[i])) 
		i++;
	token->str = ft_substr(str, 0, i, minishell->garbagecmd);
	token->type = WORD;
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
	{
		ft_error(minishell, "syntax error\n");
		return (-1);
	}
	else
	{
		token->str = ft_substr(str, 1, i - 1, minishell->garbagecmd);
		token->type = DOUBLEQUOTE;
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
	{
		ft_error(minishell, "synthax error\n");
		return (-1);
	}
		else
	{
		token->str = ft_substr(str, 1, i - 1, minishell->garbagecmd);
		token->type = SINGLEQUOTE;
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
		{
			ft_error(minishell, "synthax error\n");
			return (-1);
		}
		else
		{
			token->str = ft_substr(str, 1, i - 1, minishell->garbagecmd);
			token->type = PARENTHESIS;
		}
	return (++i);
}

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
	return(i);
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

	i = 0;
	if (*minishell->tokenlist->size == 0)
		return (-1);
	if (*minishell->tokenlist->size == 1 && ft_type(minishell->tokenlist->start) == SPACES)
		return (-1);
	if (ft_type(minishell->tokenlist->start->back) == SPACES && ft_type(minishell->tokenlist->start->back->back) == PIPE)
		return (-1);
	if (ft_type(minishell->tokenlist->start->back) == PIPE)
		return (-1);
	token = ft_malloc(sizeof(*token), minishell->garbagecmd);
	if (!token)
		ft_exit(minishell, "malloc error\n");
	ft_lstnew(token, minishell->tokenlist, minishell->garbagecmd);
	if (minishell->tokenlist->start->back == 0)
		ft_exit(minishell, "malloc error\n");
	while (str[i] && str[i] == '|')
		i++;
	token->str = ft_substr(str, 0, i, minishell->garbagecmd);
	if (i == 1)
		token->type = PIPE;
	else
		token->type = OR;
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
	if (!token)
		ft_exit(minishell, "malloc error\n");
	ft_lstnew(token, minishell->tokenlist, minishell->garbagecmd);
	if (minishell->tokenlist->start->back == 0)
		ft_exit(minishell, "malloc error\n");
	if (str[i] <= '9' && str[i] >= '0')
		i++;
	else
	{
		while (str[i] && !ft_isendword(str[i]) && str[i] != '=' && str[i] != '+' && str[i] != '/' && str[i] != '"')
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
		else if (*str == '(')
			i = ft_tokenparenthesis(minishell, str);
		else if (*str == '<')
			i = ft_tokeninbraket(minishell, str);
		else if (*str == '>')
			i = ft_tokenoutbraket(minishell, str);
		else if (*str == '|')
			i = ft_tokenpipe(minishell, str);
		else if (*str == '&')
			i = ft_tokenand(minishell, str);
		else if (*str == '$')
			i = ft_tokendollar(minishell, str);
		else
			i = ft_tokenword(minishell, str);
		if (i == -1)
			return (-1);
		else
			str = str + i;
	}
	return (0);
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

int	ft_parenthesischeck(char *str)
{
	int		i;

	i = 1;
	while (str[i] && str[i] != ')')
		i++;
	if (str[i] == '\0')
		return (i);
	else
		return (++i);
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
	while (*str)
	{
		if (*str == '(')
			str = str + ft_parenthesischeck(str);
		else if (*str == ')')
			return (0);
		else
			str++;
	}
	return (1);
}

int	ft_tokencreate(t_minishell *minishell, char *str)
{
	if (ft_numbercheck(str))
	{
		if (ft_char(minishell, str) == -1)
			return (-1);
		if (ft_type(minishell->tokenlist->start->back) == SPACES)
			ft_lstdelone(minishell->tokenlist->start->back, 0);
		if (ft_type(minishell->tokenlist->start->back) == PIPE)
			return (-1);
		ft_tokennl(minishell);	
	}
	else
		ft_error(minishell, "synthax error\n");
		// message d'erreur a paufiner pour preciser quelle erreur de synthax
	return (0);
}
