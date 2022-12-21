/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_ascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:28:59 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 14:28:59 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sort_ascii(char **envp_l, int ret, int i)
{
	char	*tmp;

	ret = size_env(envp_l);
	tmp = ft_strdup(envp_l[i]);
	free(envp_l[i]);
	envp_l[i] = envp_l[i + 1];
	envp_l[i + 1] = tmp;
	return (ret);
}
