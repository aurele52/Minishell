/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 09:52:01 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/28 15:12:10 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlengnl(char *str);
int	ft_atoignl(const char *str);

char	*ft_itoagnl(int n, char *str, char *str2)
{
	int	nb;
	int	i;

	if (n == 0)
	{
		str[0] = '0';
		return (str2);
	}
	i = 0;
	nb = n;
	while (nb > 0)
	{
		nb = nb / 10;
		i++;
	}
	str[i--] = 0;
	while (n > 0)
	{
		str[i] = n % 10 + '0';
		n = n / 10;
		i--;
	}
	return (str2);
}

char	*ft_return(char *str, char *buffer)
{	
	buffer[0] = -1;
	if (str[0] == 0)
		return (0);
	return (str);
}

void	ft_read(char *buffer, int fd)
{
	int	ret;

	ret = read(fd, buffer, BUFFER_SIZE);
	if (ret == BUFFER_SIZE)
		buffer[BUFFER_SIZE] = -1;
	if (ret < BUFFER_SIZE)
		buffer[ret] = 0;
}

char	*ft_gnl2(char *str, char *buffer, int fd, t_pos *garbage)
{
	int	mem;
	int	i;

	i = 0;
	while (1)
	{
		i = ft_atoignl(buffer) + 1;
		if (buffer[0] == 0 || buffer[i] == 0)
		{
			i = 0;
			ft_read(buffer, fd);
		}
		mem = i;
		while (buffer[i] != '\n' && buffer[i] != 0 && buffer[i] != -1)
			i++;
		str = ft_strjoin(str, ft_substr(&buffer[mem],
					0, i - mem + 1, garbage), garbage);
		if (buffer[i] == '\n')
			return (ft_itoagnl(i, buffer, str));
		if (buffer[i] == 0)
			return (ft_return(str, buffer));
		if (buffer[i] == -1)
			buffer[0] = 0;
	}
	return (0);
}

char	*get_next_line(int fd, t_pos *garbage)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*str;

	if (fd < 0 || fd > 2000 || buffer[0] == -1 || BUFFER_SIZE <= 0)
		return (0);
	str = ft_malloc(sizeof(char), garbage);
	str[0] = 0;
	return (ft_gnl2(str, buffer, fd, garbage));
}
