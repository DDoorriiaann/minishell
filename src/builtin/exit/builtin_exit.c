#include "minishell.h"

static void	numeric_argument_required(char *arg)
{
	ft_putstr_fd("exit\n", 1);
	ft_putstr_fd("Mickeytotal: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

static void	too_many_arguments(void)
{	
	ft_putstr_fd("exit\n", 1);
	ft_putstr_fd("Mickeytotal: exit: ", 2);
	ft_putstr_fd("too many arguments\n", 2);
	g_return = 1;
}

static int	check_number_of_arg(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
		i++;
	return (i - 1);
}

static void	ft_exit(char **argv, char **envp_l, t_pipes_data *pipes_data)
{
	free_2d_arr(argv);
	free_2d_arr(envp_l);
	free_forks(pipes_data);
	free(pipes_data->pipes_cmds);
	exit(g_return);
}
int	is_valid_number(const char *nptr)
{
	int					i;
	unsigned long long	nbr;
	int					neg;

	i = 0;
	nbr = 0;
	neg = 0;
	if (nptr[0] == '+' || nptr[0] == '-')
	{
		if (nptr[0] == '-')
			neg = 1;
		i++;
	}
	while ((nptr[i] != '\0') && (nptr[i] >= '0') && (nptr[i] <= '9'))
	{
		nbr = nbr * 10 + (nptr[i] - '0');
		if (neg == 0 && nbr > 9223372036854775807)
			return (0);
		if (neg == 1 && nbr > 9223372036854775808ULL)
			return (0);
		i++;
	}
	return (1);
}

int	arg_isdigit(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '+' || arg[0] == '-')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}
void	builtin_exit(char **argv, char **envp_l, t_pipes_data *pipes_data)
{
	int	i;
	int	number_arg;

	i = 1;
	number_arg = check_number_of_arg(argv);
	if (number_arg == 0)
	{	
		ft_putstr_fd("exit\n", 2);
		g_return = 0;
		ft_exit(argv, envp_l, pipes_data);
	}
	if ((!arg_isdigit(argv[i]) || !is_valid_number(argv[i])) && number_arg >= 1)
	{
		numeric_argument_required(argv[i]);
		g_return = 2;
		ft_exit(argv, envp_l, pipes_data);
	}
	if (arg_isdigit(argv[i]) && number_arg == 1)
	{
		g_return = ft_atoi(argv[i]) % 256;
		ft_putstr_fd("exit\n", 1);
		ft_exit(argv, envp_l, pipes_data);
	}
	too_many_arguments();
	ft_exit(argv, envp_l, pipes_data);
}
