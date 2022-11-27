#include "minishell.h"
#include <sys/types.h>

int	count_pipes(char **argv)
{
	int	i;
	int	pipes_count;

	pipes_count = 0;
	i = 0;
	while (argv[i])
	{
		if (ft_strlen(argv[i]) == 1 && argv[i][0] == '|')
			pipes_count++;
		i++;
	}
	return (pipes_count);
}

int	count_pipe_args(char **argv, int i)
{
	int	args_count;

	args_count = 0;
	while (argv[i] && ft_strlen(argv[i]) != 1 && argv[i][0] != '|')
	{
		args_count++;
		i++;
	}
	return (args_count);
}

int	copy_args_adresses(char **argv, int i, t_pipes_init *pipes_init,
		char ***pipes_args)
{
	while (argv[i] && ft_strlen(argv[i]) != 1 && argv[i][0] != '|')
	{
		pipes_args[pipes_init->pipe_nb][pipes_init->pipe_arg] = argv[i];
		pipes_init->pipe_arg++;
		i++;
	}
	pipes_args[pipes_init->pipe_nb][pipes_init->pipe_arg] = NULL;
	return (i);
}

int	fill_pipes_args(char ***pipes_args, char **argv)
{
	int				i;
	t_pipes_init	pipes_init;

	i = 0;
	pipes_init.pipe_nb = 0;
	while (argv[i])
	{
		pipes_init.args_count = 0;
		pipes_init.pipe_arg = 0;
		if (argv[i] && ft_strlen(argv[i]) != 1 && argv[i][0] != '|')
		{
			pipes_init.args_count = count_pipe_args(argv, i);
			pipes_args[pipes_init.pipe_nb] = malloc(sizeof(char *)
					* (pipes_init.args_count + 1));
			if (!pipes_args[pipes_init.pipe_nb])
				return (-1);
			i = copy_args_adresses(argv, i, &pipes_init, pipes_args);
		}
		pipes_init.pipe_nb++;
		if (argv[i])
			i++;
	}
	return (0);
}

int	init_pipes_data(t_pipes_data *pipes, int pipes_count)
{
	int		i;

	pipes->pipes_count = pipes_count;
	pipes->pipe_fd = malloc(sizeof(int *) * pipes_count);
	if (!pipes->pipe_fd)
		return (1);
	i = 0;
	while (i < pipes_count)
	{
		pipes->pipe_fd[i] = malloc (sizeof(int) * 2);
		if (!pipes->pipe_fd)
			return (1);
		i++;
	}
	pipes->pid = malloc(sizeof(pid_t) * pipes_count);
	if (!pipes->pid)
		return (1);
	pipes->fd_in = malloc(sizeof(int) * pipes_count);
	if (!pipes->fd_in)
		return (1);
	pipes->fd_out = malloc(sizeof(int) * pipes_count);
	if (!pipes->fd_out)
		return (1);
	return (0);
}

char	***pipes_parser(char **argv, char **envp_l, t_pipes_data *pipes)
{
	char	***pipes_args;
	int		pipes_count;

	pipes_count = count_pipes(argv);
	if (pipes_count)
		pipes->pipes_detected = TRUE;
	(void)envp_l;
	pipes_args = malloc (sizeof(char **) * (pipes_count + 2));
	fill_pipes_args(pipes_args, argv);
	init_pipes_data(pipes, pipes_count);
	//interpret_env_variables(argv, envp_l, pipes->status_code);
	//argv = handle_infile_redirection(argv, redirections);
	//argv = handle_outfile_redirection(argv, redirections);
	//remove_quotes(argv);
	return (pipes_args);
}
