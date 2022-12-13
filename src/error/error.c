# include "minishell.h"

void	ft_cmd_not_found(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, ": command not found\n", 20);
	g_return = 127;
}

void	ft_cmd_error(char *cmd)
{	
	if (access(cmd, F_OK) == -1)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory", 2);
		ft_putstr_fd("\n", 2);
		g_return = 127;
		return ;
	}
	if (access(cmd, X_OK) == -1)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": Permission denied", 2);
		ft_putstr_fd("\n", 2);
		g_return = 126;
		return ;
	} 
	if (access(cmd, F_OK | X_OK) == 0)
	{
		if ((cmd[0] == '.' && cmd[1] == '/') || cmd[0] == '/')
		{
			ft_putstr_fd("exec error : Is a directory", 2);
			ft_putstr_fd("\n", 2);
			g_return = 126;
		}
		else
		{
			ft_putstr_fd("exec error : command not found", 2);
			ft_putstr_fd("\n", 2);
			g_return = 127;

		}
	}
}

void	ft_error(void)
{
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

int	ft_error_return(void)
{
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (1);
}
