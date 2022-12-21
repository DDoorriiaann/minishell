/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_unset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:29:19 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 14:29:20 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_syntax_unset(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
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

void	print_error_unset(char *argv)
{
	ft_putstr_fd("Mickeytotal: unset: `", 2);
	ft_putstr_fd(argv, 2);
	ft_putstr_fd("':not a valid identifier\n", 2);
}
