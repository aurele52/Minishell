/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:47:48 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/02 12:48:04 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_envlist(t_minishell *minishell, char *str)
{
	int		lol;
	t_list	*line;

	lol = 0;
	line = minishell->actenv->start;
	while (line != minishell->actenv->start || lol++ == 0)
	{
		if (ft_strcmp(ft_name(line->content), str) == 0)
			return (line);
		line = line->next;
	}
	return (0);
}
