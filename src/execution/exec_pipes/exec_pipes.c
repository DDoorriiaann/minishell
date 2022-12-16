#include "minishell.h"


void	redirect_fork_stdin(t_fork *cur_fork)
{
	if (cur_fork->redirections->in_redir_type == 1)
	{
		cur_fork->redirections->fd_in
			= open(cur_fork->redirections->infile, O_RDONLY);
		if (cur_fork->redirections->fd_in < 0)
		{
			perror("");
			cur_fork->redirections->fd_in = open("/dev/null", O_RDONLY);
		}
		dup2(cur_fork->redirections->fd_in, STDIN_FILENO);
	}
	else if (cur_fork->redirections->in_redir_type == 2)
	{	
		cur_fork->redirections->here_doc = open(cur_fork->redirections->here_doc_path, O_RDONLY);
		if (cur_fork->redirections->here_doc == -1)
			perror("heredoc error");
		cur_fork->redirections->old_stdin = dup(0);
		dup2(cur_fork->redirections->here_doc, STDIN_FILENO);
	}
}

void	child(int i, char **paths, t_pipes_data *pipes_data, char ** envp_l)
{
	t_fork	*cur_fork;

	cur_fork = pipes_data->fork[i];
	redirect_fork_stdin(cur_fork);
	if (i == 0)
		dup2(pipes_data->pipe_b[WRITE], STDOUT_FILENO);
	else if (i == pipes_data->pipes_count)
	{
		if (i % 2 == 0)
			dup2(pipes_data->pipe_a[READ], STDIN_FILENO);
		else
			dup2(pipes_data->pipe_b[READ], STDIN_FILENO);
	}
	else
	{
		if (i % 2 == 0)
		{
			dup2(pipes_data->pipe_a[READ], STDIN_FILENO);
			dup2(pipes_data->pipe_b[WRITE], STDOUT_FILENO);
		}
		else
		{
			dup2(pipes_data->pipe_b[READ], STDIN_FILENO);
			dup2(pipes_data->pipe_a[WRITE], STDOUT_FILENO);
		}
	}
	redirect_fork_stdout(cur_fork);
	cur_fork->is_builtin = cmd_is_builtin(pipes_data->pipes_cmds[i][0]);
	if (cur_fork->is_builtin)
	{
		cur_fork->argc = count_cur_fork_args(pipes_data->pipes_cmds[i]);
		builtins(pipes_data->pipes_cmds[i], envp_l, cur_fork->argc, pipes_data);
		exit(g_return);
	}
	cur_fork->cmd = get_cmd(pipes_data->pipes_cmds[i][0], paths);
	if (!cur_fork->cmd)
	{
		if (pipes_data->pipes_cmds[i][0][0] == '/'
				|| (pipes_data->pipes_cmds[i][0][0] == '.'
					&& pipes_data->pipes_cmds[i][0][1] == '/'))
			ft_cmd_error(pipes_data->pipes_cmds[i][0]);
		else
			ft_cmd_not_found(pipes_data->pipes_cmds[i][0]);
		//free everything needed
		exit(EXIT_FAILURE);
	}
	if (execve(cur_fork->cmd[0], pipes_data->pipes_cmds[i], envp_l) == -1)
	{
		free_2d_arr(cur_fork->cmd);
		perror("exec error");
	}
	free_2d_arr(cur_fork->cmd);
}

int	parent(int i, t_pipes_data *pipes_data)
{
	int		status;

	if (i == 0)
		close (pipes_data->pipe_b[WRITE]);
	else if (i == pipes_data->pipes_count)
	{
		if (i % 2 == 0)
			close(pipes_data->pipe_b[WRITE]);
		else
			close(pipes_data->pipe_b[WRITE]);
	}
	else
	{
		if (i % 2 == 0)
		{
			close(pipes_data->pipe_a[READ]);
			close(pipes_data->pipe_b[WRITE]);
		}
		else
		{
			close(pipes_data->pipe_b[READ]);
			close(pipes_data->pipe_a[WRITE]);
		}
	}
	status = 0;
	waitpid(pipes_data->fork[i]->pid, &status, 0);
	return (status);
}

char	**exec_pipes(t_pipes_data *pipes_data, char **envp_l)
{
	int		i;
	int		argc;
	char	**paths;
	t_fork	*cur_fork;
	int		status;

//EXECUTION WITHOUT PIPES
	if (pipes_data->pipes_count == 0)
	{
		argc = count_cur_fork_args(pipes_data->pipes_cmds[0]);
		if (argc != 0)
			envp_l = exec_without_pipes(pipes_data->pipes_cmds[0],
					envp_l, argc, pipes_data);
		return (envp_l);
	}
//EXECUTION WITH PIPES
	i = 0;
	paths = get_path(check_line_path(envp_l));
	while (i < pipes_data->pipes_count + 1)
	{
		if (i % 2 == 0)
			pipe(pipes_data->pipe_b);
		else
			pipe(pipes_data->pipe_a);
		cur_fork = pipes_data->fork[i];
		cur_fork->pid = fork();
		if (cur_fork->pid < 0)
		{
			perror("fork error\n");
			//free everything
			// update status code
			return (envp_l);
		}
		else if (cur_fork->pid == 0)
			child(i, paths, pipes_data, envp_l);
		else
			status = parent(i, pipes_data);
		if (cur_fork->redirections->here_doc)
			delete_heredoc(cur_fork);
		i++;
	}
	if (WIFEXITED(status))
		g_return = WEXITSTATUS(status);
	free_2d_arr(paths);
	free_2d_arr(pipes_data->pipes_cmds[0]);
	free_2d_arr(pipes_data->pipes_cmds[1]);
	return (envp_l);
}
