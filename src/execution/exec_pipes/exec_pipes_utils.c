#include "minishell.h"

int	redirect_fork_stdin(t_fork *cur_fork)
{
	if (cur_fork->redirections->in_redir_type == 1)
	{
		cur_fork->redirections->fd_in
			= open(cur_fork->redirections->infile, O_RDONLY);
		if (cur_fork->redirections->fd_in < 0)
		{
			perror("");
			cur_fork->redirections->fd_in = open("/dev/null", O_RDONLY);
			return (ERROR);
		}
		dup2(cur_fork->redirections->fd_in, STDIN_FILENO);
	}
	else if (cur_fork->redirections->in_redir_type == 2)
	{	
		cur_fork->redirections->here_doc
			= open(cur_fork->redirections->here_doc_path, O_RDONLY);
		if (cur_fork->redirections->here_doc == -1)
			perror("heredoc error");
		cur_fork->redirections->old_stdin = dup(0);
		dup2(cur_fork->redirections->here_doc, STDIN_FILENO);
	}
	return (0);
}

void	duplicate_fds(int i, t_pipes_data *pipes_data)
{
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
}

void	quit_child(t_pipes_data *pipes_data, int i)
{
	if (pipes_data->pipes_cmds[i][0][0] == '/'
			|| (pipes_data->pipes_cmds[i][0][0] == '.'
				&& pipes_data->pipes_cmds[i][0][1] == '/'))
		ft_cmd_error(pipes_data->pipes_cmds[i][0]);
	else
		cmd_not_found(pipes_data->pipes_cmds[i][0]);
	exit(EXIT_FAILURE);
}

void	child(int i, char **paths,
			t_pipes_data *pipes_data, char **envp_l)
{
	t_fork	*cur_fork;

	ft_change_signal(SIG_DFL);
	cur_fork = pipes_data->fork[i];
	duplicate_fds(i, pipes_data);
	if (redirect_fork_stdin(cur_fork) == ERROR)
		exit (1);
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
		quit_child(pipes_data, i);
	if (execve(cur_fork->cmd[0], pipes_data->pipes_cmds[i], envp_l) == -1)
	{
		free_2d_arr(cur_fork->cmd);
		perror("exec error");
	}
	free_2d_arr(cur_fork->cmd);
}

void	close_fds(int i, t_pipes_data *pipes_data)
{
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
}
