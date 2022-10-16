#include "minishell.h"

static int	insert_var_value(char *updated_arg, t_env_var *var, int end)
{
	int	i;

	i = 0;
	while (var->value[i])
	{
		updated_arg[end] = var->value[i];
		i++;
		end++;
	}
	return (end);
}

static void	replace_var_by_content(char **argv, int index,
			int start, t_env_var *var)
{
	char	*updated_arg;
	int		i;

	updated_arg = malloc(ft_strlen(argv[index])
			+ var->len - (ft_strlen(var->name)) + 1);
	i = backup_arg_before_var(updated_arg, argv[index], start);
	start = start + ft_strlen(var->name);
	i = insert_var_value(updated_arg, var, i);
	backup_arg_after_var(updated_arg, argv[index], i, start);
	free(argv[index]);
	argv[index] = updated_arg;
}

int	interpret_current_env_variable(char **argv, int start,
		int arg_index, char **envp)
{
	t_env_var	*var;
	int			value_start;
	int			value_len;

	var = malloc(sizeof(t_env_var));
	var->index = env_variable_name_exists(argv[arg_index], start + 1, envp);
	var->len = ft_strlen(envp[var->index]);
	var->name = extract_env_variable_name(argv[arg_index], start + 1);
	value_start = ft_strlen(var->name);
	var->value = ft_substr(envp[var->index], value_start,
			var->len - value_start);
	replace_var_by_content(argv, arg_index, start, var);
	value_len = ft_strlen(var->value);
	free(var->value);
	free(var->name);
	free(var);
	return (start + value_len - 1);
}
