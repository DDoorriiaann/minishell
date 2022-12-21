/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var_by_status_code.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:23:58 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 14:23:59 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	insert_status_code_value(char *updated_arg,
		char *s_code_value, int end)
{
	int	i;

	i = 0;
	while (s_code_value[i])
	{	
		updated_arg[end] = s_code_value[i];
		i++;
		end++;
	}
	return (end);
}

void	replace_var_by_status_code(char **argv, int start, int index)
{
	char	*updated_arg;
	char	*s_code_value;
	int		i;
	char	*arg;

	arg = argv[index];
	s_code_value = ft_itoa(g_return);
	updated_arg = malloc(ft_strlen(arg) - 2 + ft_strlen(s_code_value) + 1);
	i = backup_arg_before_var(updated_arg, arg, start);
	i = insert_status_code_value(updated_arg, s_code_value, i);
	backup_arg_after_var(updated_arg, arg, i, start + 2);
	free(argv[index]);
	free(s_code_value);
	argv[index] = updated_arg;
}
