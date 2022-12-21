#include "minishell.h"

int	delete_var_inside_arg(char **argv, int start, int index)
{
	char		*updated_arg;
	t_env_var	*var;
	int			end;

	var = malloc(sizeof(t_env_var));
	var->name = extract_env_variable_name(argv[index], start + 1);
	var->name_len = ft_strlen(var->name);
	updated_arg = malloc((ft_strlen(argv[index]) - var->name_len + 1) + 1);
	backup_arg_before_var(updated_arg, argv[index], start);
	end = start;
	backup_arg_after_var(updated_arg, argv[index],
		end, start + var->name_len + 1);
	free(argv[index]);
	free(var->name);
	free(var);
	argv[index] = updated_arg;
	return (start - 1);
}
