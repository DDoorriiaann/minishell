#include "minishell.h"

int	check_if_new_variables(char **argv, char **envp_l)
{
	int	i;
	int	new_vars;

	i = 1;
	new_vars = 0;
	while (argv[i])
	{	
		if (check_syntax(argv[i]) == FALSE)
			ft_putstr_fd("bash :export: not a valid identifier\n", 2);
		else if (variable_found_inside_env(argv[i], envp_l) == FALSE)
			new_vars++;
		i++;
	}
	return (new_vars);
}

void	update_variable(char **envp_l, char *var, int index)
{
	free(envp_l[index]);
	envp_l[index] = ft_strdup(var);
}

char	*extract_arg_after_equal(char *argv)
{
	char	*new_arg;
	int		start;
	int		len;

	start = size_arg_before_equal(argv);
	len = size_arg(argv);
	new_arg = ft_substr(argv, start + 1, len);
	return (new_arg);
}

void	join_variable(char **envp_l, char *var, int index)
{
	int		i;
	char	*tmp;

	i = 0;
	var = extract_arg_after_equal(var);
	tmp = ft_strdup(envp_l[index]);
	while (tmp[i])
		i++;
	free(envp_l[index]);
	envp_l[index] = ft_strjoin(tmp, var);
	free(tmp);
	free(var);
}

int	check_arg(char **envp_l, char *argv)
{
	int	i;
	int	len;

	i = 0;
	len = len_arg(argv);
	while (envp_l[i])
	{
		if (ft_strncmp(envp_l[i], argv, len) == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	check_char_equal(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (argv[i] == '+' && argv[i + 1] == '=')
			return (2);
		if (argv[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	update_envp_l(char **argv, char **envp_l)
{
	int		len;
	int		i;
	int		var_index;

	len = 0;
	while (envp_l[len])
		len++;
	i = 1;
	while (argv[i])
	{
		var_index = check_arg(envp_l, argv[i]);
		if (var_index != -1)
		{
			if (check_char_equal(argv[i]) == 1)
				update_variable(envp_l, argv[i], var_index);
			if (check_char_equal(argv[i]) == 2)
				join_variable(envp_l, argv[i], var_index);
		}
		else if (check_syntax(argv[i]) == TRUE)
			envp_l[len++] = ft_strdup(argv[i]);
		i++;
	}
	envp_l[len] = NULL;
}
