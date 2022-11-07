/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgirardo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:33:30 by mgirardo          #+#    #+#             */
/*   Updated: 2022/11/07 14:33:31 by mgirardo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_minishell *minishell, t_command *command)
{
	ft_posprint(minishell, minishell->actenv, &ft_printenv, command->ofdout);	
	minishell->laststatus = 0;
}
