#include "minishell.h"

void	exec_fork_cmd(char **paths, t_pipes_data *pipes,
			char **argv, char **envp_l)
{
	ft_change_signal(SIG_DFL);
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
	waitpid(pipes->fork[0]->pid, &g_return, 0);
	if (g_return == 2)
	{
		printf("\n");
		g_return = 130;
	}
	else if (g_return == 131)
		printf("Quit (core dumped)\n");
	else
		g_return = WEXITSTATUS(g_return);
}

static void	fork_without_pipe(t_pipes_data *pipes, char **paths,
		char **argv, char **envp_l)
{
	pipes->fork[0]->pid = fork();
	if (pipes->fork[0]->pid == -1)
		perror("fork error");
	if (pipes->fork[0]->pid == 0)
		exec_fork_cmd(paths, pipes, argv, envp_l);
	else
		wait_child(pipes);
}

char	**exec_without_pipes(char **argv, char **envp_l,
			int argc, t_pipes_data *pipes)
{
	char	**paths;

	pipes->fork[0]->is_builtin = cmd_is_builtin(argv[0]);
	if (pipes->fork[0]->is_builtin)
	{
		envp_l = exec_builtin(argv, envp_l, argc, pipes);
		ft_signal();
		return (envp_l);
	}
	paths = get_path(check_line_path(envp_l));
	pipes->fork[0]->cmd = get_cmd(argv[0], paths);
	if (!pipes->fork[0]->cmd)
	{
		handle_cmd_error(argv, paths);
		ft_signal();
		return (envp_l);
	}
	fork_without_pipe(pipes, paths, argv, envp_l);
	if (pipes->fork[0]->redirections->here_doc)
		delete_heredoc(pipes->fork[0]);
	ft_free_all_arr(paths, pipes->fork[0]->cmd);
	ft_signal();
	return (envp_l);
}
