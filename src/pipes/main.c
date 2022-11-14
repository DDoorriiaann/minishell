/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:27:41 by dguet             #+#    #+#             */
/*   Updated: 2022/09/13 19:06:09 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;

	if (argc < 5)
	{
		ft_putstr_fd("Wrong number of arguments\n", 2);
		return (MISSING_ARGS);
	}
	data = malloc(sizeof (t_data));
	if (!data)
		return (MALLOC_ERROR);
	init_data(data, argc);
	get_files(argv, argc, data);
	get_cmds(argv, argc, data);
	data->paths = get_paths(envp);
	find_cmd_path(data);
	if (!data->pathnames[0] || !data->pathnames[1])
		alert_command_error(data);
	ft_split_commands(data);
	exec_cmds(data, envp);
	ft_free_all(data);
}
