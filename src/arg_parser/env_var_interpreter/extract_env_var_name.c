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
