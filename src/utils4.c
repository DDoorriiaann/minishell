#include "minishell.h"

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

	i = 1;
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
