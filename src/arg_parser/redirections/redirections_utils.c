#include "minishell.h"

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
		return (TRUE);
	if (arg_len == 2 && (argv[arg_index][0] == chevron_type && argv[arg_index][1] == chevron_type) && argv[arg_index + 1])
		return (TRUE);
	return (FALSE);
}

void	reset_redirections(t_redirections *redirections)
{
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
