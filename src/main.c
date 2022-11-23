/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:45:28 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/18 18:48:01 by mgirardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_readline(char *prompt, t_pos *garbage)
{
	char	*str;

	rl_outstream = stderr;
	str = readline(prompt);
	ft_lstnew(str, garbage, 0);
	if (garbage->start->back == 0)
		return (0);
	return (str);
}

void	ft_minishell(t_minishell *minishell)
{
	char			*str;

	str = 0;
	while (1)
	{
		str = ft_readline("Minishell> ", minishell->garbagecmd);
		if (!str)
			ft_exit(minishell, "exit\n");
		if (str[0] != '\0')
			add_history(str);
		if (ft_tokencreate(minishell, str) == 0
			|| *minishell->tokenlist->size != 0)
		{
			ft_tokenredirclean(minishell);
			if (*minishell->tokenlist->size != 0)
			{
				ft_heredocclean(minishell);
				ft_tokencmdclean(minishell);
				ft_child(minishell, minishell->tokenlist->start);
			}
			ft_error(minishell, ft_itoa(minishell->laststatus,
					minishell->garbage));
		}
	}
}

int	main(int argc, char **argv, char **env)
{
	t_minishell		*minishell;

	signal(SIGINT, &ft_signal_main);
	signal(SIGQUIT, &ft_signal_main);
	rl_outstream = stderr;
	if (!env || !env[0])
	{
		write(2, "Missing env\n", ft_strlen("Missing env\n"));
		return (1);
	}
	if (argc != 1)
	{
		write(2, "error arg\n", ft_strlen("error arg\n"));
		return (1);
	}
	(void)argv;
	minishell = ft_minishellinit(env);
	ft_minishell(minishell);
}
