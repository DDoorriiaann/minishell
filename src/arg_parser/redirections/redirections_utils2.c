/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:24:40 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 15:38:35 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

void	reset_redirections(t_pipes_data *pipes_data)
{
	int	i;

	i = 0;
	while (i < pipes_data->pipes_count + 1)
	{
		if (pipes_data->fork[i]->redirections->infile)
		{
			if (pipes_data->fork[i]->redirections->fd_in > 0)
				close(pipes_data->fork[i]->redirections->fd_in);
			free(pipes_data->fork[i]->redirections->infile);
		}
		if (pipes_data->fork[i]->redirections->outfile)
		{
			if (pipes_data->fork[i]->redirections->fd_out > 0)
				close(pipes_data->fork[i]->redirections->fd_out);
			free(pipes_data->fork[i]->redirections->outfile);
		}
		i++;
	}
}

int	save_out_filename(t_redirections *redirections, char *arg, int i, int end)
{
	int	j;

	redirections->outfile = malloc(redirections->out_filename_len + 1);
	if (!redirections->outfile)
		return (-1);
	j = 0;
	while (arg[i] && is_chevron(arg[i]))
		i++;
	while (i < end)
	{
		redirections->outfile[j] = arg[i];
		i++;
		j++;
	}
	redirections->outfile[j] = '\0';
	return (j);
}

int	save_in_filename(t_redirections *redirections, char *arg, int i, int end)
{
	int		j;
	char	*str;

	str = malloc(redirections->in_filename_len + 1);
	if (!str)
		return (-1);
	j = 0;
	while (arg[i] && is_chevron(arg[i]))
		i++;
	while (i < end)
	{
		str[j] = arg[i];
		i++;
		j++;
	}
	str[j] = '\0';
	if (redirections->in_redir_type == 1)
		redirections->infile = str;
	else if (redirections->in_redir_type == 2)
		redirections->delimiter = str;
	return (j);
}

int	find_chevron(char *arg)
{
	int	start;

	start = 0;
	while (arg[start] && !is_chevron(arg[start]))
		start++;
	return (start);
}

char	**handle_joined_chevron(char **argv, int arg_index,
		t_redirections *redirections)
{
	if (!redirections->in_error)
	{
		if (redirections->infile)
			free(redirections->infile);
		redirections->infile = NULL;
	}
	if (redirections->delimiter)
		free(redirections->delimiter);
	redirections->delimiter = NULL;
	extract_infile_name(argv, arg_index, redirections);
	if (!argv[arg_index][0])
		argv = delete_argument(argv, arg_index, 1);
	return (argv);
}
