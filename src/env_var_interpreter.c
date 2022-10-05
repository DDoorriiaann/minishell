#include "minishell.h"

int	env_variable_name_exists(char *arg, int start, char **envp)
{
	char	*env_variable_name;
	int		variable_index;

	env_variable_name = extract_env_variable_name(arg, start);
	variable_index = variable_found_inside_env(env_variable_name, envp);
	free(env_variable_name);
	if (variable_index)
		return (variable_index);
	else
		return (ERROR);
}

void	replace_var_by_content(char **argv, int index, int start, t_env_var var)
{
	char	*updated_arg;
	int		i;

	updated_arg = malloc(var.len - (ft_strlen(var.name)) + 1);
	updated_arg[var.len - ft_strlen(var.name)] = '\0';
	i = -1;
	while (++i < start)
		updated_arg[i] = argv[index][i];
	while (*var.value)
	{
		updated_arg[i] = *var.value;
		var.value++;
		i++;
	}
	start = start + ft_strlen(var.name);
	while (argv[index][start])
	{
		updated_arg[i] = argv[index][start];
		start++;
		i++;
	}
	free(argv[index]);
	argv[index] = updated_arg;
}

int	interpret_env_variable(char **argv, int start, int arg_index, char **envp)
{
	t_env_var	var;
	int			value_start;
	int			value_len;

	var.index = env_variable_name_exists(argv[arg_index], start + 1, envp);
	var.len = ft_strlen(envp[var.index]);
	var.name = extract_env_variable_name(argv[arg_index], start + 1);
	value_start = ft_strlen(var.name);
	var.value = ft_substr(envp[var.index], value_start, var.len - value_start);
	replace_var_by_content(argv, arg_index, start, var);
	value_len = ft_strlen(var.value);
	free(var.value);
	free(var.name);
	return (start + value_len);
}

void	update_argv_with_env_variables(int index, char **argv, char **envp)
{
	int		start;
	char	*arg;

	arg = argv[index];
	start = 0;
	while (arg[start])
	{
		if (arg[start] == '$')
		{	
			if (!arg[start + 1] || ft_isspace(arg[start + 1]))
			{
				start++;
				continue ;
			}
			else if (env_variable_name_exists(arg, start + 1, envp) != ERROR)
				start = interpret_env_variable(argv, start, index, envp) - 1;
			else
			{
				delete_var_inside_arg(argv, start, index);
				arg = argv[index];
				continue ;
			}		
		}
		arg = argv[index];
		start++;
	}
}

void	remove_arg(char **argv, int i)
{
	while (argv[i + 1])
	{
		free(argv[i]);
		argv[i] = ft_strdup(argv[i + 1]);
		i++;
	}
	free(argv[i]);
	argv[i] = NULL;
}

void	interpret_env_variables(char **argv, char **envp)
{
	int	i;

	i = 0;
	while (argv[i])
	{	
		update_argv_with_env_variables(i, argv, envp);
		if (!argv[i][0])
		{	
			remove_arg(argv, i);
			continue ;
		}
		i++;
	}
}

