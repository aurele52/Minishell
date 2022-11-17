/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preexit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgirardo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:33:53 by mgirardo          #+#    #+#             */
/*   Updated: 2022/11/16 15:35:52 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_preexit(t_minishell *minishell, t_command *command)
{
//	printf("exit\n");
/* 
	The exit status shall be n, if specified, except that the behavior is
	unspecified if n is not an unsigned decimal integer or is greater than 255.
	Otherwise, the value shall be the exit value of the last command executed, or
	zero if no command was executed. When exit is executed in a trap action, the
	last command is considered to be the command that executed immediately
	preceding the trap action.
 */
	ft_exit(minishell, command->cmd[0]);
}
