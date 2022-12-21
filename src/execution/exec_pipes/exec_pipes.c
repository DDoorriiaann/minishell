#include "minishell.h"

int	parent(int i, t_pipes_data *pipes_data)
{
	close_fds(i, pipes_data);
//	waitpid(pipes_data->fork[i]->pid, &g_return, 0);
	if (g_return == 2)
	{
		printf("\n");
		g_return = 130;
	}
	else if (g_return == 131)
		printf("Quit (core dumped)\n");
	else
		g_return = WEXITSTATUS(g_return);
	ft_signal();
	return (g_return);
}

char	**single_fork(t_pipes_data *pipes_data, char **envp_l)
{
	int		argc;

	argc = count_cur_fork_args(pipes_data->pipes_cmds[0]);
	if (argc != 0)
		envp_l = exec_without_pipes(pipes_data->pipes_cmds[0],
				envp_l, argc, pipes_data);
	else if (pipes_data->fork[0]->redirections->here_doc != -1)
		delete_heredoc(pipes_data->fork[0]);
	return (envp_l);
}

int	init_pipes(t_pipes_data *pipes_data, int i)
{
	if (i % 2 == 0)
	{
		if (pipe(pipes_data->pipe_b) == -1)
			return (ERROR);
	}
	else
	{
		if (pipe(pipes_data->pipe_a) == -1)
			return (ERROR);
	}
	return (0);
}

int	multiple_forks(t_pipes_data *pipes_data, char **envp_l, char **paths)
{
	t_fork	*cur_fork;
	int		i;
	int		status;

	i = 0;
	while (i < pipes_data->pipes_count + 1)
	{
		if (init_pipes(pipes_data, i))
			return (ERROR);
		cur_fork = pipes_data->fork[i];
		cur_fork->pid = fork();
		if (cur_fork->pid < 0)
		{
			ft_signal();
			return (ERROR);
		}
		else if (cur_fork->pid == 0)
			child(i, paths, pipes_data, envp_l);
		else
		{
			if (i == pipes_data->pipes_count)
				waitpid(pipes_data->fork[i]->pid, &g_return, 0);
			status = parent(i, pipes_data);
		}
		if (cur_fork->redirections->here_doc)
			delete_heredoc(cur_fork);
		i++;
	}
	return (status);
}

char	**exec_pipes(t_pipes_data *pipes_data, char **envp_l)
{
	char	**paths;
	int		status;

	ft_change_signal(SIG_IGN);
	if (pipes_data->pipes_count == 0)
	{
		envp_l = single_fork(pipes_data, envp_l);
		return (envp_l);
	}
	paths = get_path(check_line_path(envp_l));
	status = multiple_forks(pipes_data, envp_l, paths);
	if (WIFEXITED(status))
		g_return = WEXITSTATUS(status);
	free_2d_arr(paths);
	ft_signal();
	return (envp_l);
}
