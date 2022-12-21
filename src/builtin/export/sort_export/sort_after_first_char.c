/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_after_first_char.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:28:56 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 14:28:57 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_after_first_char(char **envp_l)
{
	int	i;
	int	j;
	int	ret;

	ret = size_env(envp_l);
	while (ret != 0)
	{
		i = 0;
		while (envp_l[i] && envp_l[i + 1])
		{
			j = 0;
			while (envp_l[i][j] == envp_l[i + 1][j])
			{
				j++;
				if (envp_l[i][j] > envp_l[i + 1][j])
					ret = sort_ascii(envp_l, ret, i);
			}
			i++;
		}
		ret--;
	}
}
