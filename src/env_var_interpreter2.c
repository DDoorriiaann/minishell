#include "minishell.h"

char	*extract_env_variable_name(char *arg, int start)
{
	int		end;
	char	*env_variable_name;
	int		i;

	end = start;
	while (arg[end] && (ft_isalnum(arg[end]) || arg[end] == '_'))
		end++;
	env_variable_name = malloc((end - start) + 2);
	i = 0;
	while (start < end)
	{
		env_variable_name[i] = arg[start];
		start++;
		i++;
	}
	env_variable_name[i] = '=';
	env_variable_name[i + 1] = '\0';
	return (env_variable_name);
}

int	variable_found_inside_env(char *env_variable_name, char **envp)
{
	int	i;
	int	len;

	len = ft_strlen(env_variable_name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], env_variable_name, len) == 0)
			return (i);
		i++;
	}
	return (FALSE);
}

void	delete_var_inside_arg(char **argv, int start, int index)
{
	char		*updated_arg;
	t_env_var	var;
	int			var_name_len;
	int			i;
	int			j;

	var.name = extract_env_variable_name(argv[index], start + 1);
	var_name_len = ft_strlen(var.name);
	updated_arg = malloc(ft_strlen(argv[index]) - var_name_len + 1);
	i = -1;
	while (++i < start)
		updated_arg[i] = argv[index][i];
	j = start + var_name_len;
	while (argv[index][j])
		updated_arg[i++] = argv[index][j];
	updated_arg[i] = '\0';
	free(argv[index]);
	argv[index] = updated_arg;
}
