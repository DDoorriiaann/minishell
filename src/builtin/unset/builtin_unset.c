#include "minishell.h"

static int	len_arg_unset(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] && argv[i] != '=')
		i++;
	return (i);
}

static int	check_arg_unset(char **envp_l, char *argv)
{
	int		i;
	size_t	len;

	i = 0;
	while (envp_l[i])
	{
		len = len_arg_unset(envp_l[i]);
		if (ft_strlen(argv) == len)
			if (ft_strncmp(envp_l[i], argv, len) == 0)
				return (i);
		i++;
	}
	return (-1);
}

static int	check_if_old_variables(char **argv, char **envp_l)
{
	int	i;
	int	old_vars;

	i = 1;
	old_vars = 0;
	while (argv[i])
	{
		if (check_syntax_unset(argv[i]) == FALSE)
			print_error_unset(argv[i]);
		else if (check_arg_unset(envp_l, argv[i]) != -1)
			old_vars++;
		i++;
	}
	return (old_vars);
}

static void	remove_old_variables(char **argv, char **envp_l, char **tmp_envp_l)
{
	int	i;
	int	j;
	int	k;
	int	index;

	i = 0;
	k = 0;
	while (envp_l[i])
	{
		j = 1;
		while (argv[j])
		{
			index = check_arg_unset(envp_l, argv[j]);
			if (index == i)
				break ;
			j++;
		}
		if (index != i)
		{
			tmp_envp_l[k] = ft_strdup(envp_l[i]);
			k++;
		}
		i++;
	}
	tmp_envp_l[k] = NULL;
}

char	**builtin_unset(char **envp_l, char **argv)
{
	int		old_vars;
	char	**tmp_envp_l;
	int		len;

	old_vars = check_if_old_variables(argv, envp_l);
	len = size_env(envp_l) - old_vars + 1;
	if (old_vars == 0)
		return (envp_l);
	tmp_envp_l = malloc(sizeof(char *) * len);
	if (!tmp_envp_l)
		return (NULL);
	remove_old_variables(argv, envp_l, tmp_envp_l);
	free_2d_arr(envp_l);
	g_return = 0;
	return (tmp_envp_l);
}
