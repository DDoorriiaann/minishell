/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_env_var_name.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:23:47 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 14:23:48 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_env_variable_name(char *arg, int start)
{
	int		end;
	char	*env_variable_name;
	int		i;

	end = start;
	while (arg[end] && (ft_isalnum(arg[end]) || arg[end] == '_'))
		end++;
	env_variable_name = malloc((end - start) + 1);
	i = 0;
	while (start < end)
	{
		env_variable_name[i] = arg[start];
		start++;
		i++;
	}
	env_variable_name[i] = '\0';
	return (env_variable_name);
}
