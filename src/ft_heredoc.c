/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:02:33 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/28 15:23:22 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_heredoc(t_minishell *minishell, t_token *token)
{
	int		fd;
	char	*str;
	char	*heredocnbr;
	char	*read;

	str = token->str;
	str = ft_strjoin(str, "\n", minishell->garbagecmd);
	read = 0;
	token->str = ft_strdup("./tmp/heredoc", minishell->garbagecmd);
	heredocnbr = ft_itoa(minishell->heredoc, minishell->garbagecmd);
	token->str = ft_strjoin(token->str, heredocnbr, minishell->garbagecmd);
	fd = open(token->str, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd == -1)
		write(2, "fuck me\n", 8);
	while (ft_strcmp(str, read) != 0)
	{
		read = get_next_line(0, minishell->garbagecmd);
		if (ft_strcmp(str, read) != 0)
		{
			if (token->type == HEREDOC)
				read = ft_expanddoublequote(minishell, read);
			write(fd, read, ft_strlen(read));
		}
	}
	minishell->heredoc++;
	token->type = IN;
	ft_closevaria(1, fd);
}

void	ft_heredocclean(t_minishell *minishell)
{
	t_list *tokenlist;

	tokenlist = minishell->tokenlist->start;
	while (ft_type(tokenlist) != NL)
	{
		if (ft_type(tokenlist) == HEREDOC || ft_type(tokenlist) == HEREDOCEXT)
				ft_heredoc(minishell, tokenlist->content);
		tokenlist = tokenlist->next;
	}
}
