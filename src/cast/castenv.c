/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   castenv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:43:42 by audreyer          #+#    #+#             */
/*   Updated: 2022/11/02 12:43:46 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_name(t_env *env)
{
	char	*str;

	str = (char *)env->name;
	return (str);
}

char	*ft_value(t_env *env)
{
	char	*str;

	str = (char *)env->value;
	return (str);
}
