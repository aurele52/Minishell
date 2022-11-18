/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preexit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgirardo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:33:53 by mgirardo          #+#    #+#             */
/*   Updated: 2022/11/17 18:45:53 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_preexit(t_minishell *minishell, t_command *command)
{
	char	*error;
	int		i;
	
	i = 1;
	if (ft_doublstrlen(command->cmd) == 1)
		ft_exit(minishell, "exit\n");
	else if (ft_strlen(*command->cmd) > 1 && !ft_isnum(command->cmd[i]))
		{
			error = ft_strdup(command->cmd[i], minishell->garbage);
			ft_error(minishell, "exit\n");
			error = ft_strjoin("minishell: exit: ", error, minishell->garbage);
			error = ft_strjoin(error, ": numeric argument required\n", minishell->garbage);
			ft_exit(minishell, error);
		}
	else if (ft_doublstrlen(command->cmd) > 2)
		ft_error(minishell, "minishell: exit: too many arguments\n");
	else
	{
		i = (ft_atoi(command->cmd[i]) % 256);
		ft_error(minishell, "exit\n");
		ft_exit(minishell, ft_itoa(i, minishell->garbage));
	}
}

//	printf("exit\n");
/* 
	The exit status shall be n, if specified, except that the behavior is
	unspecified if n is not an unsigned decimal integer or is greater than 255.
	Otherwise, the value shall be the exit value of the last command executed, or
	zero if no command was executed. When exit is executed in a trap action, the
	last command is considered to be the command that executed immediately
	preceding the trap action.
 */
// if command->cmd[1] < 0 || command->cmd > 255 --> undefined behavior

/*
	ajouter check lettre, on veut que des chiffres, exit quqnd meme mais mettre
	message derreur type <bash: exit: <command->cmd[1]>: numeric argument required>
*/