#include "minishell.h"

void	delete_argument(char **argv, int arg_index, int args_to_delete)
{
	int		argc;
	char	**updated_argv;
	int		i;

	argc = count_splitted_arguments(argv);
	updated_argv = malloc(sizeof(char *) * argc - args_to_delete + 1);
	i = 0;
	while (i < arg_index)
	{
		updated_argv[i] = argv[i];
		i++;
	}
	while (argv[i + 1])
	{
		updated_argv[i] = argv[i + 1];
		i++;
	}
	updated_argv[i] = NULL;
	free_2d_arr(argv);
	argv = updated_argv;
}

void	dup_arr(char **src, char **dst)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = ft_strdup(src[i]);
		i++;
	}
	dst[i] = NULL;
}

int	check_syntax(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] && argv[i] != '=')
	{
		if (argv[i] == '+' && argv[i + 1] == '=')
			return (TRUE);
		if (i == 0 && argv[i] != '_' && ft_isalpha(argv[i]) == 0)
			return (FALSE);
		if (argv[i] != '_' && ft_isalnum(argv[i]) == 0)
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	size_arg_before_equal(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] && argv[i] != '=')
		i++;
	return (i);
}

int	size_arg(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}
