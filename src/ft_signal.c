/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgirardo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:27:18 by mgirardo          #+#    #+#             */
/*   Updated: 2022/10/26 19:27:20 by mgirardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_signal(int sig, siginfo_t *siginfo, void *ucontext)
{
	(void)siginfo;
	(void)ucontext;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		// rl_replace_line("exit", 0);
		/* 
			try to find a way to replace str by exit thanks to the rl librarie
		 */
		rl_on_new_line();
		rl_redisplay();
	}
}
