#include "minishell.h"

static int	check_echo(char *echo)
{
	int	i;

	i = 1;
	while (echo[i])
	{
		if (echo[i] != 'n')
			return (NOT_MULTIPLE);
		i++;
	}
	return (MULTIPLE_N);
}

void	builtin_echo(char **argv)
{
	int		i;
	int		ret;

	i = 1;
	ret = 0;
	while (argv[i] && strncmp(argv[i], "-n", 2) == 0)
	{
		if (check_echo(argv[i]) == MULTIPLE_N)
			ret = 1;
		else
			break ;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		i++;
		if (argv[i])
			ft_putstr_fd(" ", 1);
	}
	if (ret == 0)
		ft_putstr_fd("\n", 1);
	g_return = 0;
}
