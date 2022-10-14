/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:07:09 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/14 18:31:10 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_minishell *minishell, char *str)
{
	if (str)
		write(2, str, ft_strlen(str));
	if (minishell->garbagecmd != 0)
		ft_posclear(minishell->garbagecmd, 2);
	if (minishell->garbage != 0)
		ft_posclear(minishell->garbage, 2);
	exit(0);
}
