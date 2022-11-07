#include "minishell.h"

int	check_syntax(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] && argv[i] != '=')
	{
		if (i != 0 && argv[i] == '+' && argv[i + 1] == '=')
			return (TRUE);
		if (i == 0 && argv[i] != '_' && ft_isalpha(argv[i]) == 0)
			return (FALSE);
		if (argv[i] != '_' && ft_isalnum(argv[i]) == 0)
			return (FALSE);
		i++;
	}
	if (i != 0)
		return (TRUE);
	return (FALSE);
}

void	print_error(char *argv)
{
	ft_putstr_fd("Mickeytotal: export: `", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}
