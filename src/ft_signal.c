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
		// write(1, "ctrl-C\n", 7);
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (sig == SIGQUIT)
	{
		write(1, "\33[2K\r", 5);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_signalhd(int sig, siginfo_t *siginfo, void *ucontext)
{
	(void)siginfo;
	(void)ucontext;
	if (sig == SIGINT)
	{
/*
	minishell: warning: here-document at line <where we are at> delimited by end-of-file
	(wanted `<heredoc delimiter>')
*/
	}
	else if (sig == SIGQUIT)
	{
		write(1, "\33[2K\r", 5);
		rl_on_new_line();
		rl_redisplay();
	}
}

/*
	rl_clear_history
		Clear the history list by deleting all of the entries, in the same manner
		as the History library’s clear_history() function. This differs from
		clear_history because it frees private data Readline saves in the history
		list
	rl_on_new_line,
		Tell the update routines that we have moved onto a new (empty) line,
		usually after ouputting a newline
	rl_replace_line
		Replace the contents of rl_line_buffer with text. The point and mark are
		preserved, if possible. If clear_undo is non-zero, the undo list associated
		with the current line is cleared
	rl_redisplay
		Change what's displayed on the screen to reflect the current contents of
		rl_line_buffer
*/