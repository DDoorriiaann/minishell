#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

int	exec_cmd(char **argv, char **envp_l, t_pipes_data *pipes)
{
	int		pid = 0;
	int		status = 0;
	char	**paths;
	char	**cmd;
	int		status_code;

	status_code = 0;
	if (!argv[0])
		return (EXIT_FAILURE);
	paths = get_path(check_line_path(envp_l));
	cmd = get_cmd(argv[0], paths);
	if (!cmd)
	{
		free_2d_arr(paths);
		ft_error_cmd(argv[0]);
		return (127);
	}
	pid = fork();
	(void)pipes;
	if (pid == -1)
		perror("fork error");
	if (pid == 0)
	{
	//	if (pipes->redirections->infile)
	//	{
	//		pipes->redirections->fd_in = open(pipes->redirections->infile, O_RDONLY);
	//		dup2(pipes->redirections->fd_in, STDIN_FILENO);
	//	}
	//	if (pipes->redirections->outfile)
	//	{
	//		dup2(pipes->redirections->fd_out, STDOUT_FILENO);
	//	}
		if (execve(cmd[0], argv, envp_l) == -1)
		{
			ft_free_all_arr(paths, cmd);
			perror("exec error");
		}
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status_code = WEXITSTATUS(status);
//	if (pipes->redirections->fd_out)
//		pipes->redirections->outfile = NULL;
//	close(pipes->redirections->fd_out);
	ft_free_all_arr(paths, cmd);
	return (status_code);
}

static char	**builtins(char **argv, char **envp_l, int argc, t_pipes_data *pipes_data)
{
	if ((ft_strcmp(argv[0], "echo")) == 0)
		builtin_echo(argv);
	else if ((ft_strcmp(argv[0], "pwd")) == 0)
		builtin_pwd();
	else if ((ft_strcmp(argv[0], "cd")) == 0)
		builtin_cd(argv[0], envp_l);
	else if ((ft_strcmp(argv[0], "export")) == 0)
		envp_l = builtin_export(envp_l, argv, argc);
	else if ((ft_strcmp(argv[0], "exit")) == 0)
		builtin_exit(argv, envp_l, pipes_data);
	else if ((ft_strcmp(argv[0], "env")) == 0)
		builtin_env(envp_l);
	else if ((ft_strcmp(argv[0], "unset")) == 0)
		envp_l = builtin_unset(envp_l, argv);
	else if (*argv[0])
		g_return = exec_cmd(argv, envp_l, pipes_data);
	return (envp_l);
}

int	count_cur_pipe_args(char **pipe_args)
{
	int	i;

	i = 0;
	while (pipe_args[i])
		i++;
	return (i);
}

char	**exec_pipes(t_pipes_data *pipes_data, char **envp_l)
{
	//int	i;
	int		argc;
	char	**paths;
	t_fork	*cur_fork;
	int		status = 0;

	//i = 0;
	if (pipes_data->pipes_count == 0)
	{
		argc = count_cur_pipe_args(pipes_data->pipes_cmds[0]);
		if (argc != 0)
			envp_l = builtins(pipes_data->pipes_cmds[0], envp_l, argc, pipes_data);
	}
	else if (pipes_data->pipes_count > 0)
	{

		paths = get_path(check_line_path(envp_l));
		if (pipes_data->pipes_count == 1)
		{
			if (pipe(pipes_data->fork[0]->pipe_fd) < 0)
			{
				perror("pipe error\n");
				//free everything
				// update status code
				return (envp_l);
			}
			cur_fork = pipes_data->fork[0];
			cur_fork->pid = fork();
			if (cur_fork->pid < 0)
			{
				perror("fork error\n");
				//free everything
				// update status code
				return (envp_l);
			}
			if (cur_fork->pid == 0)
			{
				close(cur_fork->pipe_fd[0]);
				dup2(cur_fork->pipe_fd[1], STDOUT_FILENO);
				close(cur_fork->pipe_fd[1]);
				cur_fork->cmd = get_cmd(pipes_data->pipes_cmds[0][0], paths);
				if (!cur_fork->cmd)
				{
					free_2d_arr(paths);
					ft_error_cmd(pipes_data->pipes_cmds[0][0]);
					//free everything needed
					return (envp_l);
				}
				if (execve(cur_fork->cmd[0], pipes_data->pipes_cmds[0], envp_l) == -1)
				{
					ft_free_all_arr(paths, cur_fork->cmd);
					perror("exec error");
				}
				free_2d_arr(cur_fork->cmd);
				exit(EXIT_FAILURE);
			}
			else
			{
				cur_fork = pipes_data->fork[1];
				pipes_data->fork[1]->pipe_fd[0] = pipes_data->fork[0]->pipe_fd[0];
				pipes_data->fork[1]->pipe_fd[1] = pipes_data->fork[0]->pipe_fd[1];
				cur_fork->pid = fork();
				if (cur_fork->pid < 0)
				{
					perror("fork error\n");
					//free everything
					// update status code
					return (envp_l);
				}
				if (cur_fork->pid == 0)
				{
					close(cur_fork->pipe_fd[1]);
					dup2(pipes_data->fork[0]->pipe_fd[0], STDIN_FILENO);
					close(cur_fork->pipe_fd[0]);
					cur_fork->cmd = get_cmd(pipes_data->pipes_cmds[1][0], paths);
					if (!cur_fork->cmd)
					{
						free_2d_arr(paths);
						ft_error_cmd(pipes_data->pipes_cmds[1][0]);
						//free everything needed
						return (envp_l);
					}
					if (execve(cur_fork->cmd[0], pipes_data->pipes_cmds[1], envp_l) == -1)
					{
						ft_free_all_arr(paths, cur_fork->cmd);
						perror("exec error");
					}
					free_2d_arr(cur_fork->cmd);
					exit(EXIT_FAILURE);
				}
				else
				{
					status = 0;
					close(pipes_data->fork[1]->pipe_fd[0]);
					close(pipes_data->fork[1]->pipe_fd[1]);
					waitpid(pipes_data->fork[1]->pid, &status, 0);
				}
			}
			if (WIFEXITED(status))
				g_return = WEXITSTATUS(status);
			//	if (pipes->redirections->fd_out)
			//		pipes->redirections->outfile = NULL;
			//	close(pipes->redirections->fd_out);
			free_2d_arr(paths);
			free_2d_arr(pipes_data->pipes_cmds[0]);
			free_2d_arr(pipes_data->pipes_cmds[1]);
			return (envp_l);
		}
		else
			printf("multiple pipes detected \n");
	}
	return (envp_l);
}

int	prompt_shell(char **envp_l, t_pipes_data *pipes_data)
{
	char	*buffer;
	char	**argv;

	argv = NULL;
	ft_signal();
	buffer = readline("Mickeytotal$>");
	while (buffer != NULL)
	{
		add_history(buffer);
		argv = raw_input_parser(buffer);
		free(buffer);
		buffer = NULL;
		if (argv[0])
		{	
			pipes_data->pipes_cmds = pipes_parser(argv, envp_l, pipes_data);
			free_2d_arr(argv);
			envp_l = exec_pipes(pipes_data, envp_l);
			free(pipes_data->pipes_cmds);
			free_forks(pipes_data);
			//reset_redirections(pipes->redirections);
		}
		else
			free(argv);
		buffer = readline("Mickeytotal$>");
	}
	free_2d_arr(envp_l);
	printf("exit\nHave a nice day with MickeyTotal \n");
	return (0);
}
