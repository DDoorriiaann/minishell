#include "minishell.h"

void	extract_infile_name(char *arg, t_redirections *redirections)
{
	int		i;

//	if (redirections->infile)
//		free(redirections->infile);
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

static char	**fetch_infile(char **argv, int arg_index,
		t_redirections *redirections)
{
	if (is_chevron_alone(argv, arg_index, '<'))
	{	
		redirections->infile = ft_strdup(argv[arg_index + 1]);
		argv = delete_argument(argv, arg_index, 2);
	}
	else
	{
		extract_infile_name(argv[arg_index], redirections);
		argv = delete_argument(argv, arg_index, 1);
	}
	return (argv);
}

static void	check_infile_redirection(char *arg, t_redirections *redirections)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_is_quote(arg[i]))
			i = find_next_corresponding_quote(arg, i + 1, arg[i]);
		if (arg[i] == '<')
		{	
			redirections->in_redirection = TRUE;
			return ;
		}
		i++;
	}
	redirections->in_redirection = FALSE;
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
			if (chevron_alone)
				i--;
			i--;
			if (i < 0)
				i = 0;
		}
		else if (argv[i])
			i++;
		redirections->in_redirection = FALSE;
	}
	if (redirections->infile)
		redirections->in_redirection = TRUE;
	return (argv);
}
