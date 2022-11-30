/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_posprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:54:06 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/30 16:24:30 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_printenv(t_minishell	*minishell, void *ptr, int fd)
{
	t_env	*env;

	(void)minishell;
	env = (t_env *)ptr;
	if (env->lvalue != 0)
	{
		write(fd, env->name, ft_strlen(env->name));
		write(fd, "=", 1);
		write(fd, env->value, ft_strlen(env->value));
		write(fd, "\n", 1);
	}
}

void	ft_posprint(t_minishell *minishell, t_pos *pos, void (*fct)
	(t_minishell *, void *, int fd), int fd)
{
	t_list	*list;

	if (pos->start != 0)
	{
		list = pos->start;
		while (list != list->pos->start->back)
		{
			(*fct)(minishell, list->content, fd);
			list = list->next;
		}
		(*fct)(minishell, list->content, fd);
	}
}
