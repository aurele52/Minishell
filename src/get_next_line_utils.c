/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 09:52:33 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/28 15:09:09 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlengnl(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != -1)
		i++;
	return (i);
}

int	ft_atoignl(const char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	if (str[0] == '0')
		return (0);
	while (str[i] <= '9' && str[i] >= '0' && str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res);
}
