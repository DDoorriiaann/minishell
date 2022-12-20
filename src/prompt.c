#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

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
		argv = raw_input_parser(buffer);
		free(buffer);
		buffer = NULL;
		if (argv[0])
		{
			pipes_data->pipes_cmds = pipes_parser(argv, envp_l, pipes_data);
			free_2d_arr(argv);
			envp_l = exec_pipes(pipes_data, envp_l);
			reset_redirections(pipes_data);
			int	i = 0;
			int	j = 0;
			while (i < pipes_data->pipes_count + 1)
			{
				while (pipes_data->pipes_cmds[i][j])
				{
					free(pipes_data->pipes_cmds[i][j]);
					j++;
				}
				if (pipes_data->pipes_cmds[i])
					free(pipes_data->pipes_cmds[i]);
				i++;
			}
			free(pipes_data->pipes_cmds);
			free_forks(pipes_data);
		}
		else
			free(argv);
		ft_signal();
		buffer = readline("Mickeytotal$>");
	}
	free_2d_arr(envp_l);
	printf("exit\n");
	return (0);
}
