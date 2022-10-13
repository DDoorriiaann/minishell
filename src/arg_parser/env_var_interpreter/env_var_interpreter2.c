#include "minishell.h"

int	variable_found_inside_env(char *env_variable_name, char **envp)
{
	int	i;
	int	len;

	len = len_arg(env_variable_name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], env_variable_name, len) == 0)
			return (i);
		i++;
	}
	return (FALSE);
}

static void	backup_arg_before_var(char *backup, char *original, int end)
{
	int	i;

	i = 0;
	while (i < end)
	{	
		backup[i] = original[i];
		i++;
	}
}

static void	backup_arg_after_var(char *backup, char *original,
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

int	delete_var_inside_arg(char **argv, int start, int index)
{
	char		*updated_arg;
	t_env_var	var;
	int			var_name_len;
	int			end;

	var.name = extract_env_variable_name(argv[index], start + 1);
	var_name_len = ft_strlen(var.name);
	updated_arg = malloc((ft_strlen(argv[index]) - var_name_len) + 1);
	backup_arg_before_var(updated_arg, argv[index], start);
	end = start;
	backup_arg_after_var(updated_arg, argv[index],
		end, start + var_name_len);
	free(argv[index]);
	free(var.name);
	argv[index] = updated_arg;
	return (start - 1);
}
