/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_arg_envp_l.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:28:34 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 14:28:35 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
