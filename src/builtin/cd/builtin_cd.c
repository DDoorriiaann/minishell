#include "minishell.h"

int	builtin_cd(char *argv, char **envp_l)
{
	char	**path;
	char	buff[2048];
	char	*old_pwd;
	int		i;

	path = ft_split(argv, ' ');
	i = 1;
	if (chdir(path[i]) == -1)
		perror("chdir()");
	i = 0;
	while (envp_l[i])
	{
		if ((ft_strncmp(envp_l[i], "PWD=", 4)) == 0)
		{
			old_pwd = ft_strdup(envp_l[i] + 4);
			free(envp_l[i]);
			envp_l[i] = ft_strjoin("PWD=", getcwd(buff, 2048));
		}
		i++;
	}
	i = 0;
	while (envp_l[i])
	{
		if ((ft_strncmp(envp_l[i], "OLDPWD=", 7)) == 0)
		{
			free(envp_l[i]);
			envp_l[i] = ft_strjoin("OLDPWD=", old_pwd);
			free(old_pwd);
		}
		i++;
	}
	free_2d_arr(path);
	return (0);
}
