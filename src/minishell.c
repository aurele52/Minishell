/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <audreyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:27:29 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/12 13:55:20 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	*ft_minishellinit(int argc, char **argv, char **env)
{
	t_minishell	*minishell;
	t_pos		*garbage;

	garbage = ft_setpos(0);
	minishell = ft_malloc(sizeof(*minishell), garbage);
	minishell->garbage = garbage;
	minishell->argc = argc;
	minishell->argv = argv;
	minishell->env = env;
	minishell->error = 0;
	return (minishell);
}

void	ft_setcolor(char *color)
{
	write(1, color, ft_strlen(color));
}

void	ft_resetcolor()
{
	const char	*color = RESET;

	write(1, color, ft_strlen(color));
}

char	*ft_readline(t_pos *garbage)
{
	char	*str;

	str = readline(0);
	if (garbage != 0)
	{
		ft_lstnew(str, garbage, 0);
		if (garbage->start->back == 0)
			return (0);
	}
	return (str);
}

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;
	char	*str;

	minishell = ft_minishellinit(argc, argv, env);
	str = 0;
	while (ft_strcmp(str, "exit") != 0 && minishell->error == 0)
	{
		ft_setcolor(GREEN);
		write(1, argv[0], ft_strlen(argv[0]));
		write(1, " ", 1);
		ft_resetcolor();
		str = ft_readline(minishell->garbage);
	}
	ft_exit(minishell->garbage, minishell->error);
}
