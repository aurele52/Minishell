/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <audreyer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 19:27:29 by audreyer          #+#    #+#             */
/*   Updated: 2022/09/08 19:48:42 by audreyer         ###   ########.fr       */
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

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;
	char	*str;

	minishell = ft_minishellinit(argc, argv, env);
	str = 0;
	while (ft_strcmp(str, "exit\n") == 1 && minishell->error == 0)
	{
		ft_setcolor(GREEN);
		write(1, argv[0], ft_strlen(argv[0]));
		write(1, " ", 1);
		ft_resetcolor();
		str = get_next_line(0, minishell->garbage);
		if (str == 0)
			break;
	}
	ft_exit(minishell->garbage, minishell->error);
}
