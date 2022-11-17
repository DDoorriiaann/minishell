#include "minishell.h"

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

int	fill_pipes_args(char ***pipes_args, char **argv)
{
	int	i;
	int	pipe_nb;
	int	pipe_arg;
	int	args_count;

	i = 0;
	pipe_nb = 0;
	while (argv[i])
	{
		args_count = 0;
		pipe_arg = 0;
		if (argv[i] && ft_strlen(argv[i]) != 1 && argv[i][0] != '|')
		{
			args_count = count_pipe_args(argv, i);
			pipes_args[pipe_nb] = malloc(sizeof(char *) * (args_count + 1));
			if (!pipes_args[pipe_nb])
				return (-1);
			while (argv[i] && ft_strlen(argv[i]) != 1 && argv[i][0] != '|')
			{
				pipes_args[pipe_nb][pipe_arg] = argv[i];
				pipe_arg++;
				i++;
			}
			pipes_args[pipe_nb][pipe_arg] = NULL;
		}
		pipe_nb++;
		if (argv[i])
			i++;
	}
	return (0);
}

char	***pipes_parser(char **argv, char **envp_l, t_pipes_data *pipes)
{
	char	***pipes_args;
	int		pipes_count;

	pipes_count = count_pipes(argv);
	(void)pipes;
	(void)envp_l;
	pipes_args = malloc (sizeof(char **) * (pipes_count + 2));
	fill_pipes_args(pipes_args, argv);
	
	//interpret_env_variables(argv, envp_l, pipes->status_code);
	//argv = handle_infile_redirection(argv, redirections);
	//argv = handle_outfile_redirection(argv, redirections);
	//remove_quotes(argv);
	return (pipes_args);
}
