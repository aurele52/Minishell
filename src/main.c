/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:45:28 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/14 19:04:40 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;
	char		*str;

	minishell = ft_minishellinit(argc, argv, env);
	str = 0;
	while (minishell->error == 0)
	{
		str = ft_readline(minishell);
		ft_tokencreate(minishell, str);
		ft_posclear(minishell->garbagecmd, 1);
		minishell->tokenlist->start = 0;
		*minishell->tokenlist->size = 0;
/* 		printf("errno = %i\n", errno);
		open("leakreadline.txt", O_RDONLY);
		printf("errno = %i\n", errno);
		open("valgrind_readline_leaks_ignore.txt", O_RDONLY);
		printf("errno = %i\n", errno); */
	}
	ft_exit(minishell, minishell->error);
}
