#include "minishell.h"

static int	check_if_old_variables(char **argv, char **envp_l)
{
	int	i;
	int	old_vars;

	i = 1;
	old_vars = 0;
	while (argv[i])
	{
		if (check_syntax(argv[i]) == FALSE)
			ft_putstr_fd("bash :export: not a valid identifier\n", 2);
		else if (check_arg_unset(envp_l, argv[i]) != -1)
			old_vars++;
		i++;
	}
	return (old_vars);
}

static void remove_old_variables(char **argv, char **envp_l, char **tmp_envp_l)
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
	ft_free_arr(envp_l);
	return (tmp_envp_l);
}
