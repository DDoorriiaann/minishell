#include "minishell.h"

int	check_plus(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] != '=' && argv[i])
	{
		if (argv[i] == '+')
			return (TRUE);
		i++;
	}
	return (FALSE);
}
