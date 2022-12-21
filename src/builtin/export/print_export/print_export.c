/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:28:43 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 14:28:44 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_quotes_export(char **export_envp_l, int i, int j)
{
	ft_putchar_fd(export_envp_l[i][j], 1);
	ft_putchar_fd('\"', 1);
	while (export_envp_l[i][++j])
		ft_putchar_fd(export_envp_l[i][j], 1);
	ft_putchar_fd('\"', 1);
}

void	print_export(char **export_envp_l)
{
	int		i;
	int		j;

	i = 0;
	while (export_envp_l[i])
	{
		if (export_envp_l[i][0] == '_' && export_envp_l[i][1] == '=')
		{
			i++;
			continue ;
		}
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (export_envp_l[i][j] && export_envp_l[i][j] != '=')
		{
			ft_putchar_fd(export_envp_l[i][j], 1);
			j++;
		}
		if (export_envp_l[i][j])
			print_quotes_export(export_envp_l, i, j);
		ft_putchar_fd('\n', 1);
		i++;
	}
}
