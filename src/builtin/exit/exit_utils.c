#include "minishell.h"

int	is_valid_number(const char *nptr)
{
	int					i;
	unsigned long long	nbr;
	int					neg;

	i = 0;
	nbr = 0;
	neg = 0;
	if (nptr[0] == '+' || nptr[0] == '-')
	{
		if (nptr[0] == '-')
			neg = 1;
		i++;
	}
	while ((nptr[i] != '\0') && (nptr[i] >= '0') && (nptr[i] <= '9'))
	{
		nbr = nbr * 10 + (nptr[i] - '0');
		if (neg == 0 && nbr > 9223372036854775807)
			return (0);
		if (neg == 1 && nbr > 9223372036854775808ULL)
			return (0);
		i++;
	}
	return (1);
}

int	arg_isdigit(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '+' || arg[0] == '-')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}
