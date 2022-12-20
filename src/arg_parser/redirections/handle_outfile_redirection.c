#include "minishell.h"

static int	extract_outfile_name(char **argv,
		int arg_index, t_redirections *redirections)
{
	int		i;
	int		end;	
	char	*arg;
	char	*backup;
	int		nb_chevrons;

	arg = argv[arg_index];
	redirections->out_filename_len = get_filename_len(arg);
	backup = malloc(ft_strlen(arg) - redirections->out_filename_len + 1);
	end = find_chevron(arg);
	i = backup_arg_before_var(backup, arg, end);
	nb_chevrons = count_chevrons(arg, end);
	redirections->out_redir_type = nb_chevrons;
	end = end + redirections->out_filename_len + redirections->out_redir_type;
	backup_arg_after_var(backup, arg, i, end);
	if (!redirections->out_error)
		save_out_filename(redirections, arg, i, end);
	free(argv[arg_index]);
	argv[arg_index] = backup;
	return (redirections->out_filename_len);
}

static char	**fetch_outfile(char **argv, int arg_index,
		t_redirections *redirections)
{
	if (is_chevron_alone(argv, arg_index, '>'))
	{	
		redirections->out_redir_type = is_chevron_alone(argv, arg_index, '>');
		if (!redirections->out_error)
			redirections->outfile = ft_strdup(argv[arg_index + 1]);
		argv = delete_argument(argv, arg_index, 2);
	}
	else
	{
		extract_outfile_name(argv, arg_index, redirections);
		if (!argv[arg_index] || !argv[arg_index][0])
			argv = delete_argument(argv, arg_index, 1);
	}
	return (argv);
}

static void	check_outfile_redirection(char *arg, t_redirections *redirections)
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
		if (arg[i] == '>')
		{	
			redirections->out_redirection = TRUE;
			return ;
		}
		i++;
	}
	redirections->out_redirection = FALSE;
}

static int	prepare_in_redirection(t_redirections *redirections,
		int chevron_alone, int i)
{
	if (redirections->outfile && !redirections->out_error)
	{
		redirections->outfile
			= remove_quotes_in_filename(redirections->outfile);
		redirections->fd_out = open(redirections->outfile, O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
		if (redirections->fd_out < 0)
			redirections->out_error = 1;
	}
	if (chevron_alone)
		i--;
	i--;
	if (i < 0)
		i = 0;
	return (i);
}

char	**handle_outfile_redirection(char **argv, t_redirections *redirections)
{
	int	i;
	int	chevron_alone;

	i = 0;
	redirections->out_error = 0;
	while (argv[i])
	{
		check_outfile_redirection(argv[i], redirections);
		if (redirections->out_redirection)
		{
			chevron_alone = is_chevron_alone(argv, i, '>');
			argv = fetch_outfile(argv, i, redirections);
			prepare_in_redirection(redirections, chevron_alone, i);
		}
		else if (argv[i])
			i++;
		redirections->out_redirection = FALSE;
	}
	if (redirections->outfile)
		redirections->out_redirection = TRUE;
	return (argv);
}
