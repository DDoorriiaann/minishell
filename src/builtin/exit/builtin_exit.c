#include "minishell.h"

void	numeric_argument_required(char *argv)
{
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("Mickeytotal: exit: ", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

void	too_many_arguments(void)
{	
	ft_putstr_fd("exit\n", 2);
	ft_putstr_fd("Mickeytotal: exit: ", 2);
	ft_putstr_fd("too many arguments\n", 2);
}

static int	check_number_of_arg(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
		i++;
	return (i - 1);
}

void	builtin_exit(char **argv)
{
	int	i;
	int	j;
	int	number_arg;

	i = 1;
	j = 0;
	number_arg = check_number_of_arg(argv);
	if (ft_isdigit(argv[i][j]) == 1 && number_arg > 1)
		too_many_arguments();
	else if (ft_isdigit(argv[i][j]) == 0 && number_arg > 1)
	{
		numeric_argument_required(argv[i]);
		exit (argv[i][j]);
	}
	else if (ft_isdigit(argv[i][j]) == 0 && number_arg <= 1)
	{
		numeric_argument_required(argv[i]);
		exit (argv[i][j]);
	}
	else if (ft_isdigit(argv[i][j]) == 1 && number_arg <= 1)
	{
		ft_putstr_fd("exit\n", 2);
		exit (argv[i][j]);
	}
}
