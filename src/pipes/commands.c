/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:07:34 by dguet             #+#    #+#             */
/*   Updated: 2022/11/28 11:25:41 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_pipe(t_pipes_data *data, char **envp)	
{
	int		res;

	data->pid[0] = fork();
	if (data->pid[0] < 0)
	{
		ft_putstr_fd("error fork1\n", 2);
		return (FORK_ERROR);
	}
	if (data->pid[0] == 0)
	{
		dup2(data->fd_in[0], STDIN_FILENO);
		dup2(data->pipe_fd[0][1], STDOUT_FILENO);
		close(data->pipe_fd[0][0]);
		close(data->pipe_fd[0][1]);
		if (data->cmds_split[0][0])
			res = execve(data->pathnames[0], data->cmds_split[0], envp);
		else
			res = 1;
		if (res < 0)
			return (COMMAND_ERROR);
	}
	return (NO_ERROR);
}

int	last_pipe(t_pipes_data *data, char **envp)
{
	int	res;

	data->pid[1] = fork();
	if (data->pid[1] < 0)
	{
		ft_putstr_fd("error fork2\n", 2);
		return (2);
	}
	if (data->pid[1] == 0)
	{
		dup2(data->pipe_fd[data->pipes_count][0], STDIN_FILENO);
		dup2(data->fd_out[data->pipes_count], STDOUT_FILENO);
		close(data->pipe_fd[data->pipes_count][0]);
		close(data->pipe_fd[data->pipes_count][1]);
		if (data->cmds_split[1][0])
			res = execve(data->pathnames[1], data->cmds_split[1], envp);
		else
			res = 1;
		if (res < 0)
			return (2);
	}
	return (NO_ERROR);
}

void	close_pipe(t_pipes_data *data)
{
	int	status;

	close(data->pipe_fd[data->pipes_count][0]);
	close(data->pipe_fd[data->pipes_count][1]);
	close(data->fd_in[data->pipes_count]);
	close(data->fd_out[data->pipes_count]);
	status = 0;
	waitpid(data->pid[0], &status, 0);
	status = 0;
	waitpid(data->pid[data->pipes_count], &status, 0);
	if (data->tmp_infile == TRUE)
		unlink("tmp_infile");
}

t_error	exec_cmds(t_pipes_data *data, char **envp)
{
	data->fd_in[0] = open(data->files[0], O_RDONLY);
	data->fd_out[0] = open(data->files[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (data->fd_in[0] == -1)
	{
		perror("");
		data->tmp_infile = 1;
		data->fd_in[0] = open("tmp_infile", O_RDONLY | O_CREAT | O_TRUNC, 0644);
	}
	if (pipe(data->pipe_fd[0]) < 0)
	{
		ft_putstr_fd("error pipe\n", 2);
		return (PIPE_ERROR);
	}
	if (data->cmds_split[0] && data->cmds_split[1])
	{	
		first_pipe(data, envp);
		if (data->pid[0] > 0)
		{
			last_pipe(data, envp);
			if (data->pid[data->cmds_count - 1] > 0)
				close_pipe(data);
		}
	}
	return (NO_ERROR);
}
