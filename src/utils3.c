#include "minishell.h"

int	size_env(char **envp_l)
{
	int	i;

	i = 0;
	while (envp_l[i])
		i++;
	return (i);
}

int	sort_ascii(char **envp_l, int ret, int i)
{
	char	*tmp;

	ret = size_env(envp_l);
	tmp = ft_strdup(envp_l[i]);
	free(envp_l[i]);
	envp_l[i] = envp_l[i + 1];
	envp_l[i + 1] = tmp;
	return (ret);
}

void	sort_first_char(char **envp_l)
{
	int	i;
	int	j;
	int	ret;

	j = 0;
	ret = size_env(envp_l);
	while (ret != 0)
	{
		i = 0;
		while (envp_l[i] && envp_l[i + 1])
		{
			if (envp_l[i][j] > envp_l[i + 1][j])
				ret = sort_ascii(envp_l, ret, i);
			i++;
		}
		ret--;
	}
}

void	sort_after_first_char(char **envp_l)
{
	int	i;
	int	j;
	int	ret;

	ret = size_env(envp_l);
	while (ret != 0)
	{
		i = 0;
		while (envp_l[i] && envp_l[i + 1])
		{
			j = 0;
			while (envp_l[i][j] == envp_l[i + 1][j])
			{
				j++;
				if (envp_l[i][j] > envp_l[i + 1][j])
					ret = sort_ascii(envp_l, ret, i);
			}
			i++;
		}
		ret--;
	}
}

int	len_arg(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] && argv[i] != '=' && argv[i] != '+')
		i++;
	return (i);
}
