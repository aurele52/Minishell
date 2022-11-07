/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgirardo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:08:01 by mgirardo          #+#    #+#             */
/*   Updated: 2022/10/27 01:13:43 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(t_minishell *minishell, char *str)
{
	minishell->laststatus = ft_errorstr(str);
	printf("in ft_error\n");//
	if (str)
		write(2, str, ft_strlen(str));
	if (minishell->garbagecmd != NULL)
		ft_posclear(minishell->garbagecmd, 1);
	minishell->tokenlist->start = 0;
	*minishell->tokenlist->size = 0;
}
