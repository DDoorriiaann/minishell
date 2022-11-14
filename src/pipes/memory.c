/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:08:16 by dguet             #+#    #+#             */
/*   Updated: 2022/09/13 18:32:01 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	init_data(t_data *data, int argc)
{	
	data->paths = NULL;
	data->pathnames = NULL;
	data->cmds = NULL;
	data->cmds_split = NULL;
	data->files = NULL;
	data->cmds_count = argc - 3;
	data->tmp_infile = FALSE;
}

void	free_pathnames(char **pathnames, int count)
{
	int	i;

	if (!pathnames)
		return ;
	i = 0;
	while (i < count)
	{
		free(pathnames[i]);
		pathnames[i] = NULL;
		i++;
	}
	free(pathnames);
	pathnames = NULL;
}

void	ft_free_all(t_data *data)
{
	ft_free_arr(data->paths);
	free_pathnames(data->pathnames, 2);
	free(data->cmds);
	ft_free_arr3d(data->cmds_split);
	free(data->files);
	free(data);
}

void	ft_free_arr(char **arr)
{
	int	i;

	i = 0;
	if (!arr)
		return ;
	while (arr[i])
	{
		if (arr[i] != NULL)
			free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
	arr = NULL;
}

void	ft_free_arr3d(char ***arr)
{
	int	i;
	int	j;

	i = 0;
	if (!arr)
		return ;
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
