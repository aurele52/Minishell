/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_posprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 17:54:06 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/13 15:05:44 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_printtoken(void *ptr)
{
	t_token	*token;

	token = (t_token *)ptr;
	write(2, token->tokenstr, ft_strlen(token->tokenstr));
	write(2, "\n", 1);
	ft_putnbrfd(token->tokentype, 2);
	write(2, "\n", 1);
}

void	ft_posprint(t_pos *pos, void (*fct)(void *))
{
	t_list	*list;

	if (pos->start != 0)
	{
		list = pos->start;
		while (list != list->pos->start->back)
		{
			(*fct)(list->content);
			list = list->next;
		}
		(*fct)(list->content);
	}
}
