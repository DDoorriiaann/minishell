#include "minishell.h"

static void	replace_old_pwd(char **envp_l, char *old_pwd)
{
	int	i;

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
}

static void	replace_pwd(char **envp_l, char **old_pwd)
{
	int		i;
	char	buff[2048];

	i = 0;
	while (envp_l[i])
	{
		if ((ft_strncmp(envp_l[i], "PWD=", 4)) == 0)
		{
			*old_pwd = ft_strdup(envp_l[i] + 4);
			free(envp_l[i]);
			envp_l[i] = ft_strjoin("PWD=", getcwd(buff, 2048));
		}
		i++;
	}
}

int	builtin_cd(char **args, char **envp_l, int argc)
{
	char	*old_pwd;

	if (argc > 2)
	{
		ft_putstr_fd("Mickeytotal: cd: too many arguments\n", 2);
		return (1);
	}
	else if (chdir(args[1]) == -1)
	{
		perror("chdir()");
		return (1);
	}
	old_pwd = NULL;
	replace_pwd(envp_l, &old_pwd);
	replace_old_pwd(envp_l, old_pwd);
	return (0);
}
