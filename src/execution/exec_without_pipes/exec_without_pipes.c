#include "minishell.h"

int	redirect_stdin(t_pipes_data *pipes)
{
	if (pipes->fork[0]->redirections->in_redir_type == 1)
	{
		pipes->fork[0]->redirections->fd_in
			= open(pipes->fork[0]->redirections->infile, O_RDONLY);
		if (pipes->fork[0]->redirections->fd_in == -1)
		{
			perror(" ");
			pipes->fork[0]->redirections->fd_in
				= open("dev/null", O_RDONLY);
			return (ERROR);
		}
		pipes->fork[0]->redirections->old_stdin = dup(0);
		dup2(pipes->fork[0]->redirections->fd_in, STDIN_FILENO);
	}
	else if (pipes->fork[0]->redirections->in_redir_type == 2)
	{	
		pipes->fork[0]->redirections->here_doc = open(pipes->fork[0]->redirections->here_doc_path, O_RDONLY);
		if (pipes->fork[0]->redirections->here_doc == -1)
			perror("heredoc error");
		pipes->fork[0]->redirections->old_stdin = dup(0);
		dup2(pipes->fork[0]->redirections->here_doc, STDIN_FILENO);
	}
	return (0);
}

int	redirect_stdout(t_pipes_data *pipes)
{
	if (pipes->fork[0]->redirections->out_redir_type == 1)
		pipes->fork[0]->redirections->fd_out = open(
				pipes->fork[0]->redirections->outfile,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (pipes->fork[0]->redirections->out_redir_type == 2)
		pipes->fork[0]->redirections->fd_out = open(
				pipes->fork[0]->redirections->outfile,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (pipes->fork[0]->redirections->fd_out < 0)
	{
		perror(" ");
		if (pipes->fork[0]->redirections->in_redirection)
		{	
			dup2(pipes->fork[0]->redirections->old_stdin, 0);
			close(pipes->fork[0]->redirections->old_stdin);
		}
		g_return = 1;
		return (ERROR);
	}
	pipes->fork[0]->redirections->old_stdout = dup(1);
	dup2(pipes->fork[0]->redirections->fd_out, STDOUT_FILENO);
	return (0);
}

void	restore_stdout(t_pipes_data *pipes)
{
	dup2(pipes->fork[0]->redirections->old_stdout, 1);
	close(pipes->fork[0]->redirections->old_stdout);
}

void	restore_stdin(t_pipes_data *pipes)
{
	dup2(pipes->fork[0]->redirections->old_stdin, 0);
	close(pipes->fork[0]->redirections->old_stdin);
}

char	**exec_builtin(char **argv, char **envp_l, int argc, t_pipes_data *pipes)
{
	if (pipes->fork[0]->redirections->in_redir_type)
		if (redirect_stdin(pipes) == ERROR)
			return (envp_l);
	if (pipes->fork[0]->redirections->outfile)
		if (redirect_stdout(pipes) == ERROR)
			return (envp_l);
	envp_l = builtins(argv, envp_l, argc, pipes);
	if (pipes->fork[0]->redirections->out_redirection)
		restore_stdout(pipes);
	if (pipes->fork[0]->redirections->in_redirection)
		restore_stdin(pipes);
	return (envp_l);
}

int	is_composed_path(char *arg)
{
	if (arg[0] == '/' || (arg[0] == '.' && arg[1] == '/'))
		return (1);
	else
		return (0);
}

void	exec_fork_cmd(char **paths, t_pipes_data *pipes, char **argv, char **envp_l)
{
	if (pipes->fork[0]->redirections->in_redir_type)
	{	
		if (redirect_stdin(pipes) == ERROR)
		{
			free_2d_arr(pipes->fork[0]->cmd);
			exit (1);
		}
	}
	if (pipes->fork[0]->redirections->outfile)
		redirect_fork_stdout(pipes->fork[0]);
	if (execve(pipes->fork[0]->cmd[0], argv, envp_l) == -1)
	{
		ft_cmd_error(pipes->fork[0]->cmd[0]);
		free_2d_arr(pipes->fork[0]->cmd);
	}
	free_2d_arr(paths);
	if (pipes->fork[0]->redirections->in_redirection)
	{	
		dup2(pipes->fork[0]->redirections->old_stdin, 0);
		close(pipes->fork[0]->redirections->old_stdin);
	}
	exit(g_return);
}

void	wait_child(t_pipes_data *pipes)
{
	int		status;

	status = 0;
	waitpid(pipes->fork[0]->pid, &status, 0);
	if (WIFEXITED(status))
		g_return = WEXITSTATUS(status);
}

void	handle_cmd_error(char **argv, char **paths)
{
	free_2d_arr(paths);
	if (is_composed_path(argv[0]))
		ft_cmd_error(argv[0]);
	else
		ft_cmd_not_found(argv[0]);
}

char **exec_without_pipes(char **argv, char **envp_l, int argc, t_pipes_data *pipes)
{
	char	**paths;

	pipes->fork[0]->is_builtin = cmd_is_builtin(argv[0]);
	if (pipes->fork[0]->is_builtin)
	{
		envp_l = exec_builtin(argv, envp_l, argc, pipes);
		return (envp_l);
	}
	paths = get_path(check_line_path(envp_l));
	pipes->fork[0]->cmd = get_cmd(argv[0], paths);
	if (!pipes->fork[0]->cmd)
	{
		handle_cmd_error(argv, paths);
		return (envp_l);
	}
	pipes->fork[0]->pid = fork();
	if (pipes->fork[0]->pid == -1)
		perror("fork error");
	if (pipes->fork[0]->pid == 0)
		exec_fork_cmd(paths, pipes, argv, envp_l);
	else
		wait_child(pipes);
	if (pipes->fork[0]->redirections->here_doc)
		delete_heredoc(pipes->fork[0]);
	ft_free_all_arr(paths, pipes->fork[0]->cmd);
	return (envp_l);
}
