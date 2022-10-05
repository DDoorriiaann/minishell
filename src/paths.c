/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybaudoui <ybaudoui@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 14:27:23 by ybaudoui          #+#    #+#             */
/*   Updated: 2022/09/30 16:23:15 by ybaudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**copy_envp(char **envp)
{
	char	**envp_l;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	envp_l = malloc(sizeof(char *) * (i + 1));
	envp_l[i] = NULL;
	i = 0;
	while (envp[i])
	{
		envp_l[i] = ft_strdup(envp[i]);
		i++;
	}
	return (envp_l);
}

char	*check_line_path(char **envp_l)
{
	int		i;

	i = 0;
	while (envp_l[i])
	{
		if ((ft_strncmp(envp_l[i], "PATH=", 5)) == 0)
		{
			return (envp_l[i] + 5);
		}
		i++;
	}
	return (0);
}

char	**get_path(char *envp_path)
{
	char	*tmp;
	char	**paths;
	int		i;

	i = 0;
	paths = ft_split(envp_path, ':');
	while (paths[i])
	{
		tmp = paths[i];
		paths[i] = ft_strjoin(paths[i], "/");
		free(tmp);
		tmp = NULL;
		i++;
	}
	return (paths);
}

char	**get_cmd(char *cmd, char **paths)
{
	int		i;
	char	**cmd_split;
	char	*cmd_path;

	i = 0;
	cmd_split = ft_split(cmd, ' ');
	if (access(cmd_split[0], F_OK) == 0)
		return (cmd_split);
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd_split[0]);
		if (access(cmd_path, F_OK) == 0)
		{
			free(cmd_split[0]);
			cmd_split[0] = cmd_path;
			return (cmd_split);
		}
		free(cmd_path);
		i++;
	}
	ft_free_arr(cmd_split);
	return (0);
}
