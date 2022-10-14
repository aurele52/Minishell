/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:07:09 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/14 14:08:24 by mgirardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_minishell *minishell, char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	if (minishell->garbagecmd != 0)
		ft_posclear(minishell->garbagecmd, 1);
	if (minishell->garbage != 0)
		ft_posclear(minishell->garbage, 1);
	exit(0);
}
