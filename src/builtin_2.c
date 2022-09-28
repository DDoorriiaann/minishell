# include "minishell.h"

int	size_env(char **envp_l)
{
	int	i;

	i = 0;
	while (envp_l[i])
		i++;
	return (i);
}

void	builtin_export(char **envp_l)
{
	int		i;
	int		j;
	int 	ret;
	char	*order_envp_l;

	ret = size_env(envp_l);
	order_envp_l = NULL;
	while (ret != 0)
	{
		i = 0;
		while(envp_l[i] && envp_l[i + 1])
		{
			j = 0;
			if (envp_l[i][j] > envp_l[i + 1][j])
			{
				ret = size_env(envp_l);
				order_envp_l = ft_strdup(envp_l[i]);
				envp_l[i] = envp_l[i + 1];
				envp_l[i + 1] = order_envp_l;
			}
			i++;
		}
		ret--;
	}
	i = 0;
	while(envp_l[i])
	{
		envp_l[i] = ft_strjoin("declare -x ", envp_l[i]);
		printf("%s\n", envp_l[i]);
		i++;
	}
}
