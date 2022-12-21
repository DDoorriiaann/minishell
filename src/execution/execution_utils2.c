/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:26:14 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 14:26:15 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_composed_path(char *arg)
{
	if (arg[0] == '/' || (arg[0] == '.' && arg[1] == '/'))
		return (1);
	else
		return (0);
}

void	handle_cmd_error(char **argv, char **paths)
{
	free_2d_arr(paths);
	if (is_composed_path(argv[0]))
		ft_cmd_error(argv[0]);
	else
		cmd_not_found(argv[0]);
}
