/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:45:28 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/13 19:46:11 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_minishell	*minishell;
	char		*str;

	minishell = ft_minishellinit(argc, argv, env);
	str = 0;
	while (ft_strcmp(str, "exit") != 0 && minishell->error == 0)
	{
		str = ft_readline(minishell);
		ft_tokencreate(minishell, str);
	}
	ft_exit(minishell, minishell->error);
}
