#include "minishell.h"

int	size_arg(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}
