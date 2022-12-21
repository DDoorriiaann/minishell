/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_infile_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:24:16 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 15:39:03 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	extract_infile_name(char **argv, int arg_index,
			t_redirections *redirections)
{
	int		i;
	int		end;	
	char	*arg;
	char	*backup;
	int		nb_chevrons;

	arg = argv[arg_index];
	redirections->in_filename_len = get_filename_len(arg);
	backup = malloc(ft_strlen(arg) - redirections->in_filename_len + 1);
	end = find_chevron(arg);
	i = backup_arg_before_var(backup, arg, end);
	nb_chevrons = count_chevrons(arg, end);
	redirections->in_redir_type = nb_chevrons;
	end = end + redirections->in_filename_len + redirections->in_redir_type;
	backup_arg_after_var(backup, arg, i, end);
	if (!redirections->in_error)
		save_in_filename(redirections, arg, i, end);
	free(argv[arg_index]);
	argv[arg_index] = backup;
}

static char	**fetch_infile(char **argv, int arg_index,
		t_redirections *redirections)
{
	if (is_chevron_alone(argv, arg_index, '<') == 1)
	{
		if (!redirections->in_error)
		{
			if (redirections->infile)
				free(redirections->infile);
			redirections->infile = ft_strdup(argv[arg_index + 1]);
			redirections->in_redir_type = 1;
		}
		argv = delete_argument(argv, arg_index, 2);
	}
	else if (is_chevron_alone(argv, arg_index, '<') == 2)
	{	
		if (redirections->delimiter)
			free(redirections->delimiter);
		redirections->delimiter = ft_strdup(argv[arg_index + 1]);
		redirections->in_redir_type = 2;
		argv = delete_argument(argv, arg_index, 2);
	}
	else
		argv = handle_joined_chevron(argv, arg_index, redirections);
	return (argv);
}

static void	check_infile_redirection(char *arg, t_redirections *redirections)
{
	int	i;
	int	j;

	i = 0;
	while (arg[i])
	{
		if (ft_is_quote(arg[i]))
		{	
			j = find_next_corresponding_quote(arg, i + 1, arg[i]);
			if (j != -1)
				i = j;
		}
		if (arg[i] == '<')
		{	
			redirections->in_redirection = TRUE;
			return ;
		}
		i++;
	}
	redirections->in_redirection = FALSE;
}

static int	prepare_in_redirection(t_redirections *redirections,
		int chevron_alone, int i)
{
	redirections->fd_in = -1;
	if (redirections->in_redir_type == 2)
		create_heredoc_path(redirections);
	if (redirections->infile && !redirections->in_error)
	{	
		redirections->infile = remove_quotes_in_filename(redirections->infile);
		redirections->fd_in = open(redirections->infile, O_RDONLY, 0644);
		if (redirections->fd_in < 0)
			redirections->in_error = 1;
		if (redirections->fd_in > 0)
			close(redirections->fd_in);
	}
	if (chevron_alone)
		i--;
	i--;
	if (i < 0)
		i = 0;
	return (i);
}

char	**handle_infile_redirection(char **argv, t_redirections *redirections)
{
	int	i;
	int	chevron_alone;

	i = 0;
	while (argv[i])
	{
		check_infile_redirection(argv[i], redirections);
		if (redirections->in_redirection)
		{
			chevron_alone = is_chevron_alone(argv, i, '<');
			argv = fetch_infile(argv, i, redirections);
			i = prepare_in_redirection(redirections, chevron_alone, i);
		}
		else if (argv[i])
			i++;
		redirections->in_redirection = FALSE;
	}
	if (redirections->infile)
		redirections->in_redirection = TRUE;
	return (argv);
}
