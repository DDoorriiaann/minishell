#include "minishell.h"

int	count_chevrons(char *arg, int start)
{
	int	i;

	i = 0;
	while (is_chevron(arg[start]))
	{
		i++;
		start++;
	}
	return (i);
}

int	is_chevron(char c)
{
	if (c == '<' || c == '>')
		return (TRUE);
	else
		return (FALSE);
}

int	is_chevron_alone(char **argv, int arg_index, char chevron_type)
{
	int	arg_len;

	arg_len = ft_strlen(argv[arg_index]);
	if (arg_len == 1 && argv[arg_index][0] == chevron_type && argv[arg_index + 1])
		return (1);
	if (arg_len == 2 && (argv[arg_index][0] == chevron_type && argv[arg_index][1] == chevron_type) && argv[arg_index + 1])
		return (2);
	return (FALSE);
}

void	reset_redirections(t_redirections *redirections)
{
	redirections->out_error = FALSE;
	if (redirections->infile)
	{
		free(redirections->infile);
		redirections->infile = NULL;
		redirections->in_redirection = FALSE;
	}
	if (redirections->outfile)
	{
		free(redirections->outfile);
		redirections->outfile = NULL;
		redirections->out_redirection = FALSE;
	}
}

int	get_filename_len(char *arg)
{
	int	len;
	int	i;

	len = 0;
	i = 0;
	while (arg[i] && !is_chevron(arg[i]))
		i++;
	while (arg[i] && is_chevron(arg[i]))
		i++;
	while (arg[i] && !is_chevron(arg[i]))
	{	
		i++;
		len++;
	}
	return (len);
}

int	save_out_filename(t_redirections *redirections, char *arg, int i, int end)
{
	int	j;

//	if (redirections->outfile)
//		free(redirections->outfile);
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
//	if (redirections->outfile)
//		free(redirections->outfile);

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
