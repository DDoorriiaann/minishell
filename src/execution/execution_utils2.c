#include "minishell.h"

int	is_composed_path(char *arg)
{
	if (arg[0] == '/' || (arg[0] == '.' && arg[1] == '/'))
		return (1);
	else
		return (0);
}

void	handle_cmd_error(char **argv, char **paths)
{
	free_2d_arr(paths);
	if (is_composed_path(argv[0]))
		ft_cmd_error(argv[0]);
	else
		cmd_not_found(argv[0]);
}
