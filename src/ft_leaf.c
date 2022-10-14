/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_leaf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgirardo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:12:26 by mgirardo          #+#    #+#             */
/*   Updated: 2022/10/14 21:32:21 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	DOUBLECOTE,
	SINGLECOTE,
	SPACES,

	WORD,
	PARENTHESIS,
	DASH,
	PIPE,
	AND,
	OR,
	HEREDOC,
	WRITE,
	APPEND,
	IN
};
void	ft_createleaf(t_minishell *minishell)
{
	
}

void	ft_parseleaf(t_minishell *minishell, t_pos *tokenpos)
{
	t_list	*tokenlist;
	t_token	*token;
	t_command	*command;
	int	cmd;

	command = ft_malloc(sizeof(*command), minishell->garbagecmd);
	if (!command)
		ft_exit(garbage, "malloc error\n");
	token = (t_token *)tokenlist->content;
	if (token->type == WRITE)
		command->fdout = ft_open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (token->type == APPEND)
		command->fdout = ft_open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (token->type == in)
	{
		command->fdin = ft_open(argv[1], O_RDONLY, 0444);
	}
	if (token->type = DASH  && )
	}
		
}

void	ft_leaf(t_minishell *minishell)
{
	ft_createleaf(minishell);
	ft_parseleaf(minishell);
}
