#include "minishell.h"

void	free_forks(t_pipes_data *pipes_data)
{
	int	i;

	i = 0;
	while (i < pipes_data->pipes_count + 1)
	{
		free(pipes_data->fork[i]->redirections);
		free(pipes_data->fork[i]);
		i++;
	}
	free(pipes_data->fork);
}

void	free_pipes_cmds_arr(char ***arr)
{
	int	i;
	int	j;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			free(arr[i][j]);
			arr[i][j] = NULL;
			j++;
		}
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	free_2d_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	if (arr)
	{
		free(arr);
		arr = NULL;
	}
}

void	ft_free_all_arr(char **paths, char **cmd)
{
	free_2d_arr(paths);
	free_2d_arr(cmd);
}
