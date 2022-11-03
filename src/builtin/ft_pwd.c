#include "minishell.h"

void	ft_pwd(t_minishell *minishell, t_command *command)
{
	char	*str;

	str = ft_searchinenv(minishell, "PWD");
	if (access(str, F_OK))
	{
		ft_error(minishell, "pwd: error retrieving current directory: getcwd: cannot access parent directories: No such file or directory\n");
		return ;
	}
	write(command->ofdout, str, ft_strlen(str));
	write(command->ofdout, "\n", 1);
	minishell->laststatus = 0;
}
