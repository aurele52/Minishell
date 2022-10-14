/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgirardo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 14:08:01 by mgirardo          #+#    #+#             */
/*   Updated: 2022/10/14 14:08:03 by mgirardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error(t_minishell *minishell, char *str)
{
	if (minishell->garbagecmd != NULL)
		ft_posclear(minishell->garbagecmd, 0);
	if (minishell->tokenlist != NULL)
		ft_posclear(minishell->tokenlist, 0);
	if (str)
		write(2, str, ft_strlen(str));
}
