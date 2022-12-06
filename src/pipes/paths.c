/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 11:01:44 by dguet             #+#    #+#             */
/*   Updated: 2022/11/15 15:34:57 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_path(char *env_path)
{
	char	**paths;
	char	*tmp;
	int		i;

	paths = ft_split(env_path, ':');
	i = 0;
	while (paths[i])
	{
		tmp = ft_strdup(paths[i]);
		free(paths[i]);
		paths[i] = ft_strjoin(tmp, "/");
		free(tmp);
		i++;
	}
	return (paths);
}

char	**empty_path(void)
{
	char	**empty_path;

	empty_path = malloc(sizeof(char **));
	empty_path[0] = ft_strdup("");
	return (empty_path);
}

char	**get_paths(char **envp)
{
	char	*env_path;
	char	**paths;
	int		i;

	env_path = NULL;
	i = 0;
	while (envp[i] && !env_path)
	{
		if (ft_strnstr(envp[i], "PATH=",
				ft_strlen(envp[i])) && envp[i][0] == 'P')
		{
			env_path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
			if (!env_path)
				return (NULL);
		}
		i++;
	}
	if (env_path)
	{	
		paths = split_path(env_path);
		free(env_path);
	}
	else
		paths = empty_path();
	return (paths);
}

void	get_files(char **argv, int argc, t_pipes_data *data)
{
	data->files = malloc(sizeof (char *) * 2);
	data->files[0] = argv[1];
	data->files[1] = argv[argc - 1];
}

void	find_cmd_path(t_pipes_data *data)
{
	char	**cmd_split;
	int		i;

	i = -1;
	data->pathnames = malloc (sizeof(char *) * (data->cmds_count + 1));
	while (data->cmds[++i])
	{
		if (data->cmds[i][0])
		{
			cmd_split = ft_split(data->cmds[i], ' ');
			if (is_cmd_litteral_path(data, cmd_split, i))
				continue ;
			search_valid_path(data, cmd_split, i);
			ft_free_arr(cmd_split);
		}
		else
			data->pathnames[i] = NULL;
	}
	data->pathnames[data->cmds_count] = NULL;
}
