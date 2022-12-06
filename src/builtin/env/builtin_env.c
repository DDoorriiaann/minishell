#include "minishell.h"

void	builtin_env( char **envp_l)
{
	int	i;

	i = 0;
	while (envp_l[i])
	{
		if (ft_strchr(envp_l[i], '=') != NULL)
			printf("%s\n", envp_l[i]);
		i++;
	}
	g_return = 0;
}
