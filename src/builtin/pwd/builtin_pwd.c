#include "minishell.h"

void	builtin_pwd(void)
{
	char	buffer[2048];

	if (getcwd(buffer, 2048) != NULL)
		printf("%s\n", buffer);
	else
		ft_error();
}
