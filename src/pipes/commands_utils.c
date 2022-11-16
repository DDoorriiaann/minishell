/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 18:11:29 by dguet             #+#    #+#             */
/*   Updated: 2022/11/15 15:33:47 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	alert_command_error(t_pipes_data *data)
{
	ft_putstr_fd("command not found: ", 2);
	if (!data->pathnames[0])
		ft_putstr_fd(data->cmds[0], 2);
	ft_putstr_fd(" ", 2);
	if (!data->pathnames[1])
		ft_putstr_fd(data->cmds[1], 2);
	ft_putstr_fd("\n", 2);
}

t_error	get_cmds(char **argv, int argc, t_pipes_data *data)
{
	int		i;
	int		j;

	i = 2;
	j = 0;
	data->cmds = malloc(sizeof (char *) * argc - 2);
	if (!data->cmds)
		return (MALLOC_ERROR);
	while (i < argc - 1)
	{
		data->cmds[j] = argv[i];
		i++;
		j++;
	}
	data->cmds[j] = NULL;
	return (NO_ERROR);
}

t_error	ft_split_commands(t_pipes_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (data->cmds[i])
		i++;
	data->cmds_split = malloc (sizeof (char **) * (i + 1));
	if (!data->cmds_split)
		return (MALLOC_ERROR);
	data->cmds_split[i] = NULL;
	j = 0;
	while (j < i)
	{
		if (data->cmds[j])
			data->cmds_split[j] = ft_split(data->cmds[j], ' ');
		else
			data->cmds_split[j] = NULL;
		j++;
	}
	return (NO_ERROR);
}
