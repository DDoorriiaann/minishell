#include "minishell.h"

int	len_arg(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] && argv[i] != '=' && argv[i] != '+')
		i++;
	if (argv[i] == '=')
		i++;
	return (i);
}

int	len_arg_unset(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] && argv[i] != '=')
		i++;
	return (i);
}
