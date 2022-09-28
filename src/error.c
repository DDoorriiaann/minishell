# include "minishell.h"

void	ft_error_cmd(char *str)
{
	write(2, "command '", 9);
	write(2, str, ft_strlen(str));
	write(2, "' not found\n", 12);
	exit(1);
}

void	ft_error(void)
{
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

int		ft_error_return(void)
{
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (1);
}
