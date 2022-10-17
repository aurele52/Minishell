/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <audreyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:27:29 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/18 01:26:32 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*ft_pipeinit(t_minishell *minishell)
{
	int	*i;

	i = ft_malloc(sizeof(int) * 3, minishell->garbage);
	if (!i)
		ft_exit(minishell, "malloc error\n");
	i[0] = 0;
	i[1] = 0;
	i[2] = 0;
	return (i);
}

char	**ft_envinit(char **env, t_pos *garbage)
{
	char *str;

	str = ft_unsplit(env, "+", garbage);
	return (ft_split(str, '+', garbage));
}

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
	minishell->actenv = ft_envinit(env, garbage);
	if (!minishell->actenv)
		ft_exit(minishell, "malloc error\n");
	minishell->pipe = ft_pipeinit(minishell);
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

char	*ft_readline(char *prompt, t_pos *garbage)
{
	char	*str;

	str = readline(prompt);
	ft_lstnew(str, garbage, 0);
	if (garbage->start->back == 0)
		return (0);
	return (str);
}
