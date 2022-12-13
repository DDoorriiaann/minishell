#include "minishell.h"
#include <stdio.h>
#include <unistd.h>


int	count_cur_fork_args(char **pipe_args)
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
		argc = count_cur_fork_args(pipes_data->pipes_cmds[0]);
		if (argc != 0)
			envp_l = exec_without_pipes(pipes_data->pipes_cmds[0], envp_l, argc, pipes_data);
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
				if (cur_fork->redirections->infile)
				{
					cur_fork->redirections->fd_in = open(cur_fork->redirections->infile, O_RDONLY);
					if (cur_fork->redirections->fd_in < 0)
					{
						perror("");
						cur_fork->tmp_infile = 1;
						cur_fork->redirections->fd_in = open("tmp_infile", O_RDONLY | O_CREAT | O_TRUNC, 0644);
					}
					dup2(cur_fork->redirections->fd_in, STDIN_FILENO);
				}
				close(cur_fork->pipe_fd[0]);
				dup2(cur_fork->pipe_fd[1], STDOUT_FILENO);
				close(cur_fork->pipe_fd[1]);
				if (cur_fork->redirections->outfile)
				{
					if (cur_fork->redirections->out_redir_type == 1)
						cur_fork->redirections->fd_out = open(cur_fork->redirections->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
					else if (cur_fork->redirections->out_redir_type == 2)
						cur_fork->redirections->fd_out = open(cur_fork->redirections->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
					if (cur_fork->redirections->fd_out < 0)
					{
						perror(" ");
					//	if (!cur_fork->is_builtin)
					//		free_2d_arr(cur_fork->cmd);
						exit (EXIT_FAILURE);
					}
					
					dup2(cur_fork->redirections->fd_out, STDOUT_FILENO);
				}
				cur_fork->is_builtin = cmd_is_builtin(pipes_data->pipes_cmds[0][0]);
				if (cur_fork->is_builtin)
				{
					cur_fork->argc = count_cur_fork_args(pipes_data->pipes_cmds[0]);
					builtins(pipes_data->pipes_cmds[0], envp_l, cur_fork->argc, pipes_data);
					exit(g_return);
				}
				cur_fork->cmd = get_cmd(pipes_data->pipes_cmds[0][0], paths);
				if (!cur_fork->cmd)
				{
					if (pipes_data->pipes_cmds[0][0][0] == '/' ||(pipes_data->pipes_cmds[0][0][0] == '.' && pipes_data->pipes_cmds[0][0][1] == '/'))
						ft_cmd_error(pipes_data->pipes_cmds[0][0]);
					else
						ft_cmd_not_found(pipes_data->pipes_cmds[0][0]);
					return (envp_l);
					//free everything needed
					exit(EXIT_FAILURE);
				}
				if (execve(cur_fork->cmd[0], pipes_data->pipes_cmds[0], envp_l) == -1)
				{
					free_2d_arr(cur_fork->cmd);
					perror("exec error");
				}
				free_2d_arr(cur_fork->cmd);
				if (cur_fork->tmp_infile == TRUE)
					unlink("tmp_infile");
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
					exit(EXIT_FAILURE);
				}
				if (cur_fork->pid == 0)
				{
					if (cur_fork->redirections->infile)
					{
						cur_fork->redirections->fd_in = open(cur_fork->redirections->infile, O_RDONLY);
						if (cur_fork->redirections->fd_in < 0)
						{
							perror("");
							cur_fork->tmp_infile = 1;
							cur_fork->redirections->fd_in = open("tmp_infile", O_RDONLY | O_CREAT | O_TRUNC, 0644);
						}
						dup2(cur_fork->redirections->fd_in, STDIN_FILENO);
					}
					close(cur_fork->pipe_fd[1]);
					dup2(pipes_data->fork[0]->pipe_fd[0], STDIN_FILENO);
					close(cur_fork->pipe_fd[0]);
					/*if (cur_fork->redirections->outfile)
					{
						cur_fork->redirections->fd_out = open(cur_fork->redirections->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
						if (cur_fork->redirections->fd_out < 0) 
							cur_fork->redirections->fd_out = open("/dev/null", O_WRONLY);
						dup2(cur_fork->redirections->fd_out, STDOUT_FILENO);
					}*/
					if (cur_fork->redirections->outfile)
					{
						if (cur_fork->redirections->out_redir_type == 1)
							cur_fork->redirections->fd_out = open(cur_fork->redirections->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
						else if (cur_fork->redirections->out_redir_type == 2)
							cur_fork->redirections->fd_out = open(cur_fork->redirections->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
						if (cur_fork->redirections->fd_out < 0)
						{
							perror(" ");
						//	if (!cur_fork->is_builtin)
						//		free_2d_arr(cur_fork->cmd);
							exit (EXIT_FAILURE);
						}
						
						dup2(cur_fork->redirections->fd_out, STDOUT_FILENO);
					}
					cur_fork->is_builtin = cmd_is_builtin(pipes_data->pipes_cmds[1][0]);
					if (cur_fork->is_builtin)
					{
						cur_fork->argc = count_cur_fork_args(pipes_data->pipes_cmds[1]);
						builtins(pipes_data->pipes_cmds[1], envp_l, cur_fork->argc, pipes_data);
						exit(g_return);
					}
					cur_fork->cmd = get_cmd(pipes_data->pipes_cmds[1][0], paths);
					if (!cur_fork->cmd)
					{
						if (pipes_data->pipes_cmds[0][0][0] == '/' ||(pipes_data->pipes_cmds[0][0][0] == '.' && pipes_data->pipes_cmds[0][0][1] == '/'))
							ft_cmd_error(pipes_data->pipes_cmds[0][0]);
						else
							ft_cmd_not_found(pipes_data->pipes_cmds[0][0]);
					//	ft_error_cmd(pipes_data->pipes_cmds[1][0]);
						//free everything needed
						exit(EXIT_FAILURE);
					}
					if (execve(cur_fork->cmd[0], pipes_data->pipes_cmds[1], envp_l) == -1)
					{
						free_2d_arr(cur_fork->cmd);
						perror("exec error");
					}
					free_2d_arr(cur_fork->cmd);
					if (cur_fork->tmp_infile == TRUE)
						unlink("tmp_infile");
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
	printf("exit\n");
	return (0);
}
