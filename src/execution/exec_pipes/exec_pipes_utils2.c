/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipes_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:21:36 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 15:21:52 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_pipes(t_pipes_data *pipes_data, int i)
{
	if (i % 2 == 0)
	{
		if (pipe(pipes_data->pipe_b) == -1)
			return (ERROR);
	}
	else
	{
		if (pipe(pipes_data->pipe_a) == -1)
			return (ERROR);
	}
	return (0);
}
