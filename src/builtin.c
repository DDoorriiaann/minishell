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
		free(echo[i]);
		i++;
	}
	while (echo[i])
	{
		printf("%s", echo[i]);
		free(echo[i]);
		i++;
		if (echo[i])
			printf(" ");
	}
	if (ret == 0)
		printf("\n");
	free(echo);
}
