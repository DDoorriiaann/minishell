# include "minishell.h"

void	ft_free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	ft_free_all_arr(char **paths, char **cmd)
{
	ft_free_arr(paths);
	ft_free_arr(cmd);
}
