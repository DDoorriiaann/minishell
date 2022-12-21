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

static void	ft_exit(char **envp_l, t_pipes_data *pipes_data)
{
	int	i;

	i = 0;
	free_2d_arr(envp_l);
	while (i < 2)
	{
		if (pipes_data->pipe_a[i] > 0)
			close(pipes_data->pipe_a[i]);
		if (pipes_data->pipe_b[i] > 0)
			close(pipes_data->pipe_b[i]);
		i++;
	}
	reset_redirections(pipes_data);
	free_forks(pipes_data);
	i = 0;
	free_2d_arr(pipes_data->argv);
	if (pipes_data->pipes_cmds)
		free_pipes_cmds_arr(pipes_data->pipes_cmds);
	exit(g_return);
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
		ft_exit(envp_l, pipes_data);
	}
	if ((!arg_isdigit(argv[i]) || !is_valid_number(argv[i])) && number_arg >= 1)
	{
		numeric_argument_required(argv[i]);
		g_return = 2;
		ft_exit(envp_l, pipes_data);
	}
	if (arg_isdigit(argv[i]) && number_arg == 1)
	{
		g_return = ft_atoi(argv[i]) % 256;
		ft_putstr_fd("exit\n", 1);
		ft_exit(envp_l, pipes_data);
	}
	too_many_arguments();
	ft_exit(envp_l, pipes_data);
}
