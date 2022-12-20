#include "minishell.h"

int	skip_single_quoted_content(char *arg, int start)
{
	if (arg[start] == '\''
		&& find_closing_quote(arg, start + 1, arg[start]) != ERROR)
		start = find_closing_quote(arg, start + 1, arg[start]);
	start++;
	return (start);
}

int	variable_found_inside_env(char *env_variable_name, char **envp)
{
	int	i;
	int	len;

	len = len_arg(env_variable_name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], env_variable_name, len) == 0
			&& (envp[i][len] == '=' || envp[i][len] == '\0'))
			return (i);
		i++;
	}
	return (FALSE);
}

int	backup_arg_before_var(char *backup, char *original, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{	
		backup[i] = original[i];
		i++;
	}
	return (i);
}

void	backup_arg_after_var(char *backup, char *original,
		int end, int current_char)
{
	while (original[current_char] != '\0')
	{
		backup[end] = original[current_char];
		end++;
		current_char++;
	}
	backup[end] = '\0';
}

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
