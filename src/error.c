# include "minishell.h"

void	ft_error_cmd(char *str)
{
	write(2, "command '", 9);
	write(2, str, ft_strlen(str));
	write(2, "' not found\n", 12);
	exit(1);
}
