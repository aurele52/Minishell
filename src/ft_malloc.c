/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 14:32:19 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/13 16:01:37 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_malloc(int size, t_pos *garbage)
{
	void	*new;

	new = malloc(size);
	if (new == 0)
		return (0);
	if (garbage != 0)
	{
		ft_lstnew(new, garbage, 0);
		if (garbage->start->back == 0)
		{
			free(new);
			return (0);
		}
	}
	return (new);
}
