/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:29:11 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 14:29:11 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] && arg[i] != '=')
	{
		if (i != 0 && arg[i] == '+' && arg[i + 1] == '=')
			return (TRUE);
		if (i == 0 && arg[i] != '_' && ft_isalpha(arg[i]) == 0)
			return (FALSE);
		if (arg[i] != '_' && ft_isalnum(arg[i]) == 0)
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
	g_return = 1;
}
