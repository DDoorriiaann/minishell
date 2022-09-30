#include "minishell.h"

int	check_echo(char *echo)
{
	int	i;

	i = 1;
	while (echo[i])
	{
		if (echo[i] != 'n')
			return (NOT_MULTIPLE);
		i++;
	}
	return (MULTIPLE_N);
}

void	builtin_echo(char *buffer)
{
	char	**echo;
	int		i;
	int		ret;

	i = 1;
	ret = 0;
	echo = ft_split(buffer, ' ');
	while (echo[i] && strncmp(echo[i], "-n", 2) == 0)
	{
		if (check_echo(echo[i]) == MULTIPLE_N)
			ret = 1;
		else
			break ;
		i++;
	}
	while (echo[i])
	{
		printf("%s", echo[i]);
		i++;
		if (echo[i])
			printf(" ");
	}
	if (ret == 0)
		printf("\n");
	ft_free_arr(echo);
}

void	builtin_pwd(void)
{
	char	buffer[2048];

	if (getcwd(buffer, 2048) != NULL)
		printf("%s\n", buffer);
	else
		ft_error();
}

int	builtin_cd(char *buffer, char **envp_l)
{
	char	**path;
	char	buff[2048];
	char	*old_pwd;
	int		i;

	path = ft_split(buffer, ' ');
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
	ft_free_arr(path);
	return (0);
}
