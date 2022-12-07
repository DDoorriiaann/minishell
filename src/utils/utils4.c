#include "minishell.h"

int	find_next_corresponding_quote(char *input, int end, char quote_type)
{
	while (input[end])
	{
		if (input[end] == quote_type)
			return (end);
		end++;
	}
	return (ERROR);
}

char	**delete_argument(char **argv, int arg_index, int args_to_delete)
{
	int		argc;
	char	**updated_argv;
	int		i;

	argc = count_splitted_arguments(argv);
	updated_argv = malloc(sizeof(char *) * argc - args_to_delete + 1);
	i = 0;
	while (i < arg_index)
	{
		updated_argv[i] = ft_strdup(argv[i]);
		i++;
	}
	while (argv[i + args_to_delete])
	{
		updated_argv[i] = ft_strdup(argv[i + args_to_delete]);
		i++;
	}
	updated_argv[i] = NULL;
	free_2d_arr(argv);
	return (updated_argv);
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
/*
int	check_syntax(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] && argv[i] != '=')
	{
		if (i != 0 && argv[i] == '+' && argv[i + 1] == '=')
			return (TRUE);
		if (i == 0 && argv[i] != '_' && ft_isalpha(argv[i]) == 0)
			return (FALSE);
		if (argv[i] != '_' && ft_isalnum(argv[i]) == 0)
			return (FALSE);
		i++;
	}
	if (i != 0)
		return (TRUE);
	return (FALSE);
}

void	print_error(char *argv)
{
	ft_putstr_fd("Mickeytotal: export: `", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);

}
*/
