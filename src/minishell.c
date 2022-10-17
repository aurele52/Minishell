/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <audreyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:27:29 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/14 18:53:16 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*ft_minishellinit(int argc, char **argv, char **env)
{
	t_minishell	*minishell;
	t_pos		*garbage;

	garbage = ft_setpos(0);
	minishell = ft_malloc(sizeof(*minishell), garbage);
	if (minishell == 0)
		ft_exit(minishell, "malloc error\n");
	minishell->garbage = garbage;
	minishell->argc = argc;
	minishell->argv = argv;
	minishell->env = env;
	minishell->envact = env;
	minishell->garbagecmd = ft_setpos(0);
	if (minishell->garbagecmd == 0)
		ft_exit(minishell, "malloc error\n");
	minishell->error = 0;
	minishell->prompt = ft_strjoin(ft_strjoin(
				ft_strdup("\x1b[32m", garbage), ft_strdup(argv[0], garbage),
				garbage), ft_strdup("\x1b[0m ", garbage), garbage);
	if (minishell->prompt == 0)
		ft_exit(minishell, "malloc error\n");
	minishell->tokenlist = ft_setpos(minishell->garbage);
	if (!minishell->tokenlist)
		ft_exit(minishell, "malloc error\n");
	return (minishell);
}

void	ft_setcolor(char *color)
{
	write(1, color, ft_strlen(color));
}

void	ft_resetcolor(void)
{
	const char	*color = RESET;

	write(1, color, ft_strlen(color));
}

char	*ft_readline(t_minishell *minishell)
{
	char	*str;

	str = readline(minishell->prompt);
	ft_lstnew(str, minishell->garbagecmd, 0);
	if (minishell->garbagecmd->start->back == 0)
		return (0);
	return (str);
}
