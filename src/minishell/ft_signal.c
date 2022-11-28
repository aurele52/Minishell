/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgirardo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 19:27:18 by mgirardo          #+#    #+#             */
/*   Updated: 2022/11/16 16:46:57 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//	rl_clear_history
//		Clear the history list by deleting all of the entries,
//in the same manner
//		as the History library’s clear_history() function. This differs from
//		clear_history because it frees priva
//	te data Readline saves in the history
//		list
//	rl_on_new_line,
//		Tell the update routines that we have moved onto a new (empty) line,
//		usually after ouputting a newline
//	rl_replace_line
//		Replace the contents of rl_line_buffe
//	r with text. The point and mark are
//		preserved, if possible. If clea
//	r_undo is non-zero, the undo list associated
//		with the current line is cleared
//	rl_redisplay
//		Change what's displayed on the screen to reflect the current contents of
//		rl_line_buffer

//	if (sig == SIGINT) //ctrl + c
//	else if (sig == SIGQUIT) //ctrl + /

//	if (sig == SIGINT) // ctrl + c
//		close (0); //not good enough
//	else if (sig == SIGQUIT) //ctrl + /

void	ft_signal_main(int sig)
{
	if (sig == SIGINT)
	{
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

void	ft_signalhd(int sig)
{
	if (sig == SIGINT)
	{
		g_heredoc = 130;
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		close(0);
	}
	else if (sig == SIGQUIT)
	{
		write(1, "\33[2K\r", 5);
		rl_on_new_line();
		rl_redisplay();
	}
}
