/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:26:27 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 14:26:28 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_pipes(t_pipes_data *pipes_data)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		pipes_data->pipe_a[i] = -1;
		pipes_data->pipe_b[i] = -1;
		i++;
	}
}

char	**execute_commands(t_pipes_data *pipes_data, char **argv, char **envp_l)
{
	reset_pipes(pipes_data);
	pipes_data->pipes_cmds = pipes_parser(argv, pipes_data);
	pipes_data->argv = argv;
	envp_l = exec_pipes(pipes_data, envp_l);
	reset_redirections(pipes_data);
	free_2d_arr(argv);
	free_forks(pipes_data);
	if (pipes_data->pipes_cmds)
		free_pipes_cmds_arr(pipes_data->pipes_cmds);
	return (envp_l);
}

int	prompt_shell(char **envp_l, t_pipes_data *pipes_data)
{
	char	*buffer;
	char	**argv;

	argv = NULL;
	ft_signal();
	buffer = readline("Mickeytotal$>");
	while (buffer != NULL)
	{
		add_history(buffer);
		argv = raw_input_parser(buffer, envp_l);
		free(buffer);
		buffer = NULL;
		if (argv[0])
			envp_l = execute_commands(pipes_data, argv, envp_l);
		else
			free(argv);
		ft_signal();
		buffer = readline("Mickeytotal$>");
	}
	free_2d_arr(envp_l);
	printf("exit\n");
	return (0);
}
