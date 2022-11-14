/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 17:40:26 by dguet             #+#    #+#             */
/*   Updated: 2022/09/13 17:48:09 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_cmd_litteral_path(t_data *data, char **cmd_split, int i)
{
	if (access(cmd_split[0], R_OK | X_OK) == 0)
	{
		data->pathnames[i] = ft_strdup(cmd_split[0]);
		ft_free_arr(cmd_split);
		return (1);
	}
	return (0);
}

void	search_valid_path(t_data *data, char **cmd_split, int i)
{
	int		j;

	j = -1;
	while (data->paths[++j])
	{	
		data->pathnames[i] = ft_strjoin(data->paths[j], cmd_split[0]);
		if (access (data->pathnames[i], R_OK | X_OK) == 0)
			break ;
		else
		{
			free(data->pathnames[i]);
			data->pathnames[i] = NULL;
		}
	}
}
