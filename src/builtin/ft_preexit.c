/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_preexit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgirardo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:33:53 by mgirardo          #+#    #+#             */
/*   Updated: 2022/11/16 15:35:52 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_preexit(t_minishell *minishell, t_command *command)
{
//	printf("exit\n");
	ft_exit(minishell, command->cmd[0]);
}
