/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_without_pipes_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:26:07 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 14:26:08 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
			g_return = 1;
			return (ERROR);
		}
		pipes->fork[0]->redirections->old_stdin = dup(0);
		dup2(pipes->fork[0]->redirections->fd_in, STDIN_FILENO);
	}
	else if (pipes->fork[0]->redirections->in_redir_type == 2)
	{	
		pipes->fork[0]->redirections->here_doc
			= open(pipes->fork[0]->redirections->here_doc_path, O_RDONLY);
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
