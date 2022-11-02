#include "minishell.h"

void	numeric_argument_required(char *argv)
{
	ft_putstr_fd("Mickeytotal: exit: ", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

void	too_many_arguments(char *argv)
{
	ft_putstr_fd("Mickeytotal: exit: ", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(": too many arguments\n", 2);
}

char	**builtin_exit(char **envp_l, char **argv)
{
	
}
