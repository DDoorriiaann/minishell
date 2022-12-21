#include "minishell.h"

int	check_char_equal(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '+' && argv[i + 1] == '=')
			return (2);
		if (argv[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
