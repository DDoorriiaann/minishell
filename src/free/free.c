# include "minishell.h"

void	free_2d_arr(char **arr)
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
	free_2d_arr(paths);
	free_2d_arr(cmd);
}
