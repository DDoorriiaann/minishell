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

int	check_arg_unset(char **envp_l, char *argv)
{
	int	i;
	int	len;

	i = 0;
	while (envp_l[i])
	{
		len = len_arg_unset(envp_l[i]);
		if (ft_strncmp(envp_l[i], argv, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}
