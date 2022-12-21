#include "minishell.h"

int	count_pipes(char **argv)
{
	int	i;
	int	pipes_count;

	pipes_count = 0;
	i = 0;
	while (argv[i])
	{
		if (ft_strlen(argv[i]) == 1 && argv[i][0] == '|')
			pipes_count++;
		i++;
	}
	return (pipes_count);
}

int	count_pipe_args(char **argv, int i)
{
	int	args_count;

	args_count = 0;
	while (argv[i])
	{
		if (ft_strlen(argv[i]) == 1 && argv[i][0] == '|')
			return (args_count);
		args_count++;
		i++;
	}
	return (args_count);
}
