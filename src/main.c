/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:45:28 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/18 01:25:06 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;
	char		*str;

	minishell = ft_minishellinit(argc, argv, env);
	str = 0;
	while (minishell->error == 0)
	{
		str = ft_readline(minishell->prompt, minishell->garbagecmd);
		if (str == 0)
			ft_exit(minishell, "readline error\n");
		if (ft_strlen(str) != 0)
		{
			ft_closevaria(1, 1);
			ft_tokencreate(minishell, str);
			printf("debut first-------------------\n");
			ft_posprint(minishell, minishell->tokenlist, &ft_printtoken);
			printf("fin first---------------------\n\n");
			ft_tokenredirclean(minishell);
			printf("debut second------------------\n");
			ft_posprint(minishell, minishell->tokenlist, &ft_printtoken);
			printf("fin second--------------------\n\n");
			ft_tokencmdclean(minishell);
			printf("debut third-------------------\n");
			ft_posprint(minishell, minishell->tokenlist, &ft_printtoken);
			printf("fin third---------------------\n\n");
			ft_posprint(minishell, minishell->actenv, &ft_printenv);
			// ft_child(minishell, minishell->tokenlist->start);
			ft_posclear(minishell->garbagecmd, 1);
			minishell->tokenlist->start = 0;
			*minishell->tokenlist->size = 0;
		}
/* 		printf("errno = %i\n", errno);
		open("leakreadline.txt", O_RDONLY);
		printf("errno = %i\n", errno);
		open("valgrind_readline_leaks_ignore.txt", O_RDONLY);
		printf("errno = %i\n", errno); */
	}
	ft_exit(minishell, minishell->error);
}
