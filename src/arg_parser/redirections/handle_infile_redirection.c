#include "minishell.h"

static void	extract_infile_name(char *arg, t_redirections *redirections)
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

static int	fetch_infile(char **argv, int arg_index,
		t_redirections *redirections)
{
	int	arg_len;

	arg_len = ft_strlen(argv[arg_index]);
	if (arg_len == 1 && argv[arg_index][0] == '<' && argv[arg_index + 1])
	{	
		redirections->infile = argv[arg_index + 1];
		delete_argument(argv, arg_index, 2);
		arg_index -= 2;
	}
	else
	{
		extract_infile_name(argv[arg_index], redirections);
		delete_argument(argv, arg_index, 1);
		arg_index--;
	}
	return (arg_index);
}

static void	check_infile_redirection(char *arg, t_redirections *redirections)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '<')
			redirections->in_redirection = TRUE;
		i++;
	}
	redirections->in_redirection = FALSE;
}

void	handle_infile_redirection(char **argv, t_redirections *redirections)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		check_infile_redirection(argv[i], redirections);
		if (redirections->in_redirection)
			i = fetch_infile(argv, i, redirections);
		redirections->in_redirection = FALSE;
		i++;
	}
	if (redirections->infile)
		redirections->in_redirection = TRUE;
	printf("infile : %s\n", redirections->infile);
}
