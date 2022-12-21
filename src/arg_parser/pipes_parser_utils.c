/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_parser_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:25:10 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 15:28:10 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_pipes(char **argv)
{
	int	i;
	int	pipes_count;

	pipes_count = 0;
	i = 0;
	while (argv[i])
	{
		if (ft_strlen(argv[i]) == 1 && argv[i][0] == '|')
			pipes_count++;
		i++;
	}
	return (pipes_count);
}

int	count_pipe_args(char **argv, int i)
{
	int	args_count;

	args_count = 0;
	while (argv[i])
	{
		if (ft_strlen(argv[i]) == 1 && argv[i][0] == '|')
			return (args_count);
		args_count++;
		i++;
	}
	return (args_count);
}

void	set_default_redirections(t_fork *cur_fork)
{
	cur_fork->redirections->infile = NULL;
	cur_fork->redirections->outfile = NULL;
	cur_fork->redirections->in_redir_type = 0;
	cur_fork->redirections->out_redir_type = 0;
	cur_fork->redirections->here_doc = 0;
	cur_fork->redirections->fd_in = 0;
	cur_fork->redirections->fd_out = 0;
	cur_fork->redirections->in_error = 0;
	cur_fork->redirections->out_error = 0;
}
