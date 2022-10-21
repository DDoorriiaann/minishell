#include "minishell.h"

int	size_arg_before_equal(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] && argv[i] != '=')
		i++;
	return (i);
}
