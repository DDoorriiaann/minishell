/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 15:27:41 by dguet             #+#    #+#             */
/*   Updated: 2022/11/30 16:27:40 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipex(char ***pipes_cmds, t_pipes_data *pipes, char **envp)
{
	t_pipes_data *data;
	
	data=NULL;
	init_data(pipes, pipes_cmds);

//	get_files(, argc, data);
//	get_cmds(argv, argc, data);
//	data->paths = get_paths(envp);
	find_cmd_path(data);
	if (!data->pathnames[0] || !data->pathnames[1])
		alert_command_error(data);
	ft_split_commands(data);
	exec_cmds(data, envp);
	ft_free_all(data);
	return (0);
}
