/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_posclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 22:11:43 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/12 12:35:45 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_posclear(t_pos *pos, int freee)
{
	if (pos != NULL)
	{
		while (*pos->size != 0)
			ft_lstdelone(pos->start, freee);
		if (freee == 1)
		{
			free(pos->size);
			free(pos);
		}
	}
}
