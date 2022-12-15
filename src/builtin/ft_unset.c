/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgirardo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:34:23 by mgirardo          #+#    #+#             */
/*   Updated: 2022/12/15 13:16:35 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(t_minishell *minishell, t_command *command)
{
	t_list	*envlist;
	int		i;

	i = 1;
	while (command->cmd[i])
	{
		envlist = ft_envlist(minishell, command->cmd[i]);
		if (envlist != 0)
			ft_lstdelone(envlist, 0);
		minishell->laststatus = 0;
	}
}
