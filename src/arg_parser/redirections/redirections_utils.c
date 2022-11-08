#include "minishell.h"

int	is_chevron_alone(char **argv, int arg_index)
{
	int	arg_len;

	arg_len = ft_strlen(argv[arg_index]);
	if (arg_len == 1 && argv[arg_index][0] == '<' && argv[arg_index + 1])
		return (TRUE);
	return (FALSE);
}

void	extract_file_name(char *arg, t_redirections *redirections)
{
	int		i;

	if (redirections->infile)
		free(redirections->infile);
	redirections->infile = malloc(ft_strlen(arg));
	if (!redirections->infile)
		return ;
	i = 0;
	while (arg[i + 1])
	{
		redirections->infile[i] = arg[i + 1];
		i++;
	}
	redirections->infile[i] = '\0';
}
