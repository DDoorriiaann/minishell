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
			free(pipes_data->pipes_cmds);
			free_forks(pipes_data);
			//reset_redirections(pipes->redirections);
		}
		else
			free(argv);
		buffer = readline("Mickeytotal$>");
	}
	free_2d_arr(envp_l);
	printf("exit\n");
	return (0);
}
