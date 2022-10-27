/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:45:28 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/27 13:18:03 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_minishell		*minishell;
	char			*str;
//	t_sigaction	sa;

//	sa.sa_flags = SA_SIGINFO;
//	sa.sa_sigaction = ft_signal;
//	sigemptyset(&sa.sa_mask);
//	sigaction(SIGINT, &sa, NULL);
//	sigaction(SIGQUIT, &sa, NULL);
//	sigaction(/* to be found for ctrl-\ */, &sa, NULL);
	rl_outstream = stderr;
	if (!env || !env[0])
	{
		write(2, "Missing env\n", ft_strlen("Missing env\n"));
		return (1);
	}
	minishell = ft_minishellinit(argc, argv, env);
	str = 0;
	while (minishell->error == 0)
	{
		str = ft_readline(minishell->prompt, minishell->garbagecmd);
		if (str == 0)
			ft_exit(minishell, "readline error\n");
		add_history(str);
		if (ft_strlen(str) != 0)
		{
			if (ft_tokencreate(minishell, str) == 0)
			{
				if (*minishell->tokenlist->size != 0)
				{
//					printf("debut first-------------------\n");
//					ft_posprint(minishell, minishell->tokenlist, &ft_printtoken);
//					printf("fin first---------------------\n\n");
					ft_tokenredirclean(minishell);
//					printf("debut second------------------\n");
//					ft_posprint(minishell, minishell->tokenlist, &ft_printtoken);
//					printf("fin second--------------------\n\n");
					ft_heredocclean(minishell);
					ft_tokencmdclean(minishell);
//					printf("debut third-------------------\n");
//					ft_posprint(minishell, minishell->tokenlist, &ft_printtoken);
//					printf("fin third---------------------\n\n");
//						ft_posprint(minishell, minishell->actenv, &ft_printenv);
					ft_child(minishell, minishell->tokenlist->start);
				}
			}
			ft_posclear(minishell->garbagecmd, 1);
			minishell->tokenlist->start = 0;
			*minishell->tokenlist->size = 0;
		}
	}
	ft_exit(minishell, minishell->error);
}
