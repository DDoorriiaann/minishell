#include "minishell.h"

int	check_arg(char **envp_l, char *argv)
{
	int	i;
	int	len;

	i = 0;
	while (envp_l[i])
	{
		len = len_arg(envp_l[i]);
		if (ft_strncmp(envp_l[i], argv, len) == 0)
			return (i);
		if (ft_strncmp(envp_l[i], argv, len - 1) == 0
			&& argv[len - 1] == '+')
			return (i);
		i++;
	}
	return (-1);
}
