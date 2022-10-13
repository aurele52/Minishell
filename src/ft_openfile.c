/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_openfile.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: audreyer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 11:55:54 by audreyer          #+#    #+#             */
/*   Updated: 2022/10/13 15:03:15 by audreyer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


int	ft_heredoc(t_pipex *pipex, char *limiter)
{
	int		fd;
	char	*str;

	str = 0;
	limiter = ft_strjoin(limiter, "\n", pipex->garbage);
	if (!access("heredoc_tmp", F_OK))
		unlink("heredoc_tmp");
	fd = open("heredoc_tmp", O_CREAT | O_RDWR, 0777);
	while (ft_strcmp(str, limiter) != 0)
	{
		write(0, ">", 1);
		str = get_next_line(0, pipex->garbage);
		if (str == 0)
			ft_exit(pipex->garbage, "\nheredoc error");
		if (ft_strcmp(str, limiter) != 0)
			write(fd, str, ft_strlen(str));
	}
	ft_closevaria(1, fd);
	fd = open("heredoc_tmp", O_RDONLY);
	return (fd);
}
/*
		open readonly
		int fd = open(argv[1], O_RDONLY, 0444); a verif
		open writeonly mais creer si non existant et remplace si existant pour >
		int fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644); a verif
		open writeonly mais creer si non existant et ajoute a la fin si existant pour >>
		int fd = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644); a verif

*/
