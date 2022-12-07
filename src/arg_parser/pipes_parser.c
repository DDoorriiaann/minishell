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
	while (argv[i])
	{
		if (ft_strlen(argv[i]) == 1 && argv[i][0] == '|')
		{
			i++;
			continue ;
		}
		args_count++;
		i++;
	}
	return (args_count);
}

int	duplicate_args(char **argv, int i, t_pipes_init *pipes_init,
		char ***pipes_args)
{
	while (argv[i])
	{
		if  (ft_strlen(argv[i]) == 1 && argv[i][0] == '|')
		{
			i++;
			continue ;
		}
		pipes_args[pipes_init->pipe_nb][pipes_init->pipe_arg] = ft_strdup(argv[i]);
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
		//if (!argv[i] || (ft_strlen(argv[i]) == 1 && argv[i][0] == '|'))
		//	return (1);
		pipes_init.args_count = count_pipe_args(argv, i);
		pipes_args[pipes_init.pipe_nb] = malloc(sizeof(char *)
				* (pipes_init.args_count + 1));
		if (!pipes_args[pipes_init.pipe_nb])
			return (-1);
		i = duplicate_args(argv, i, &pipes_init, pipes_args);
		pipes_init.pipe_nb++;
		if (argv[i])
			i++;
	}
	return (0);
}

int	init_pipes_data(t_pipes_data *pipes_data, int pipes_count)
{
	int		i;

	pipes_data->pipes_count = pipes_count;
	pipes_data->fork = malloc(sizeof(t_fork *) * (pipes_count + 1));
	if (!pipes_data->fork)//free
		return (1);
	i = 0;
	while (i <= pipes_count)
	{
		pipes_data->fork[i] = malloc(sizeof(t_fork));
		if (!pipes_data->fork[i])//free
			return (1);
		pipes_data->fork[i]->redirections = malloc(sizeof(t_redirections));
		if (!pipes_data->fork[i]->redirections)//free
			return (1);
		pipes_data->fork[i]->redirections->infile = NULL;
		pipes_data->fork[i]->redirections->outfile = NULL;
		pipes_data->fork[i]->pipe_fd[0] = -1;
		pipes_data->fork[i]->pipe_fd[1] = -1;
		i++;
	}	
	return (0);
}

char	***pipes_parser(char **argv, char **envp_l, t_pipes_data *pipes_data)
{
	char	***pipes_args;
	int		pipes_count;
	int		i;

	pipes_count = count_pipes(argv);
	if (pipes_count)
		pipes_data->pipes_detected = TRUE;
	(void)envp_l;
	pipes_args = malloc (sizeof(char **) * (pipes_count + 2));
	if (!pipes_args)//free
		return (NULL);
	pipes_args[pipes_count + 1] = NULL;
	fill_pipes_args(pipes_args, argv);
	init_pipes_data(pipes_data, pipes_count);
	i = 0;
	while (pipes_args[i])
	{
		interpret_env_variables(pipes_args[i], envp_l);
		pipes_args[i] = handle_infile_redirection(pipes_args[i], pipes_data->fork[i]->redirections);
		pipes_args[i] = handle_outfile_redirection(pipes_args[i], pipes_data->fork[i]->redirections);
		remove_quotes(argv);
		i++;
	}
	return (pipes_args);
}
