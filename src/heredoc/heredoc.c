/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:26:19 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 15:13:25 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_heredoc_path(t_redirections *redirections)
{
	if (redirections->here_doc_path)
		free(redirections->here_doc_path);
	redirections->here_doc_path = ft_strjoin("./here_doc",
			ft_itoa(redirections->fork_index));
	if (!redirections->here_doc_path)
		return (ERROR);
	else
		return (0);
}

void	delete_heredoc(t_fork *cur_fork)
{	
	close(cur_fork->redirections->here_doc);
	unlink(cur_fork->redirections->here_doc_path);
	free(cur_fork->redirections->here_doc_path);
}

static void	set_heredoc(char *delimiter, int heredoc_fd)
{
	char	*line;

	line = readline("> ");
	while (line && strcmp(line, delimiter))
	{
		ft_putstr_fd(line, heredoc_fd);
		write(heredoc_fd, "\n", 1);
		line = readline("> ");
	}	
	write(1, "\n", 1);
}

void	wait_heredoc(int pid)
{
	waitpid(pid, &g_return, 0);
		g_return = WEXITSTATUS(g_return);
}

void	ft_heredoc(t_fork *cur_fork)
{
	int	pid;

	cur_fork->redirections->here_doc = open(cur_fork->redirections
			->here_doc_path, O_CREAT | O_RDWR | O_APPEND, 0644);
	ft_change_signal(SIG_IGN);
	pid = fork();
	if (pid == -1)
		perror("fork error");
	if (pid == 0)
	{
		ft_signal_heredoc();
		set_heredoc(cur_fork->redirections->delimiter,
			cur_fork->redirections->here_doc);
		exit(1);
	}
	else
		wait_heredoc(pid);
	close(cur_fork->redirections->here_doc);
	ft_signal();
}
