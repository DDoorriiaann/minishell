#include "minishell.h"

int	size_env(char **envp_l)
{
	int	i;

	i = 0;
	while (envp_l[i])
		i++;
	return (i);
}

void	sort_export(char **envp_l, char *order_envp_l)
{
	int	i;
	int	j;
	int	ret;

//	j = 0;
//	ret = size_env(envp_l);
//	while (ret != 0)
//	{
//		i = 0;
//		while (envp_l[i] && envp_l[i + 1])
//		{
//			if (envp_l[i][j] > envp_l[i + 1][j])
//			{
//				ret = size_env(envp_l);
//				order_envp_l = ft_strdup(envp_l[i]);
//				free(envp_l[i]);
//				envp_l[i] = envp_l[i + 1];
//				envp_l[i + 1] = order_envp_l;
//			}
//			i++;
//		}
//		ret--;
//	}
	ret = size_env(envp_l);
	while (ret != 0)
	{
		i = 0;
		while (envp_l[i] && envp_l[i + 1])
		{
			j = 0;
			while (envp_l[i][j] == envp_l[i + 1][j])
			{
				if (envp_l[i][j] > envp_l[i + 1][j])
				{
					ret = size_env(envp_l);
					order_envp_l = ft_strdup(envp_l[i]);
					free(envp_l[i]);
					envp_l[i] = envp_l[i + 1];
					envp_l[i + 1] = order_envp_l;
				}
				j++;
			}
			i++;
		}
		ret--;
	}
}

void	builtin_export(char **envp_l)
{
	int		i;
	char	*tmp;
	char	*order_envp_l;

	i = 0;
	order_envp_l = NULL;
	sort_export(envp_l, order_envp_l);
	while (envp_l[i])
	{
		tmp = ft_strjoin("declare -x ", envp_l[i]);
		printf("%s\n", tmp);
		free(tmp);
		i++;
	}
}
