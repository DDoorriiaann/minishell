#include "minishell.h"

int	builtin_cd(char **args, char **envp_l, int argc)
{
	char	buff[2048];
	char	*old_pwd;
	int		i;

	if (argc > 2)
	{
		ft_putstr_fd(" too many arguments\n", 2);
		return (1);
	}
	else if (chdir(args[1]) == -1)
	{
		perror("chdir()");
		return (1);
	}
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
	return (0);
}
