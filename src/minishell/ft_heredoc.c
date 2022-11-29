/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:02:33 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/28 15:32:31 by mgirardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_eofheredoc(t_minishell *minishell, char *str)
{
	char	*error;

	minishell->heredocprompt++;
	error = ft_strdup("minishell: warning: here-docume", minishell->garbagecmd);
	error = ft_strjoin(error, "nt at line ", minishell->garbagecmd);
	error = ft_strjoin(error,
			ft_itoa(minishell->heredocprompt, minishell->garbagecmd),
			minishell->garbagecmd);
	error = ft_strjoin(error, " delimited by end-of-fi", minishell->garbagecmd);
	error = ft_strjoin(error, "le (wanted `", minishell->garbagecmd);
	error = ft_strjoin(error, str, minishell->garbagecmd);
	error[ft_strlen(error) - 1] = '\0';
	error = ft_strjoin(error, "')\n", minishell->garbagecmd);
	printf("%s", error);
	minishell->laststatus = 0;
	return (str);
}

char	*ft_whileheredoc(t_minishell *minishell, char *str, t_token *t, int fd)
{
	char	*read;

	read = ft_readline("> ", minishell->garbagecmd);
	if (!read && g_heredoc == 42)
		return (ft_eofheredoc(minishell, str));
	else if (!read && g_heredoc == 130)
	{
		minishell->heredocprompt++;
		minishell->laststatus = g_heredoc;
		dup2(minishell->fdutil, 0);
		return (str);
	}
	minishell->heredocprompt++;
	read = ft_strjoin(read, "\n", minishell->garbagecmd);
	if (ft_strcmp(str, read) != 0)
	{
		if (t->type == HEREDOC)
			read = ft_expanddoublequote(minishell, read);
		write(fd, read, ft_strlen(read));
	}
	return (read);
}

void	ft_heredoc(t_minishell *minishell, t_token *token)
{
	int		fd;
	char	*str;
	char	*heredocnbr;
	char	*read;

	str = token->str;
	read = 0;
	token->str = ft_strdup("./tmp/heredoc", minishell->garbagecmd);
	str = ft_strjoin(str, "\n", minishell->garbagecmd);
	heredocnbr = ft_itoa(minishell->heredoc, minishell->garbagecmd);
	token->str = ft_strjoin(token->str, heredocnbr, minishell->garbagecmd);
	fd = open(token->str, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (fd == -1)
		write(2, "Could not open file descriptor\n", 8);
	signal(SIGINT, ft_signalhd);
	signal(SIGQUIT, ft_signalhd);
	while (ft_strcmp(str, read) != 0)
		read = ft_whileheredoc(minishell, str, token, fd);
	minishell->heredoc++;
	token->type = IN;
	ft_closevaria(1, fd);
}

int	ft_heredocclean(t_minishell *minishell)
{
	t_list	*tokenlist;

	tokenlist = minishell->tokenlist->start;
	while (ft_type(tokenlist) != NL)
	{
		if (ft_type(tokenlist) == HEREDOC || ft_type(tokenlist) == HEREDOCEXT)
			ft_heredoc(minishell, tokenlist->content);
		tokenlist = tokenlist->next;
		ft_setsignalmain();
	}
	return (minishell->laststatus);
}
