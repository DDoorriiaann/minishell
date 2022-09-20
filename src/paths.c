#include "proto.h"

char	*check_line_path(char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		if ((ft_strncmp(envp[i], "PATH=", 5)) == 0)
		{
			return (envp[i] + 5);
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
