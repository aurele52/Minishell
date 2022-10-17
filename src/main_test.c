/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 19:45:28 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/13 19:54:54 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_command *command);

int	main(int argc, char **argv, char **env)
{
	// t_minishell	*minishell;
	t_command	*command;

	// minishell = ft_minishellinit(argc, argv, env);
	// (void)minishell;
	(void)argc;
	(void)env;
	command = malloc(sizeof(*command) * 1);
	command->cmd = argv;
	command->fdout = 1;
	ft_echo(command);
	return (0);
}
