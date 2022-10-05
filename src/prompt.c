#include "minishell.h"
#include <stdio.h>

void	exec_cmd(char **argv, char **envp_l)
{
	int		pid = 0;
	int		status = 0;
	char	**paths;
	char	**cmd;

	if (!argv[0])
		return ;
	paths = get_path(check_line_path(envp_l));
	cmd = get_cmd(argv[0], paths);
	if (!cmd)
	{
		ft_free_arr(paths);
		perror(argv[0]);
		return ;
	}
	pid = fork();
	if (pid == -1)
		perror("fork error");
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
	{
		if (execve(cmd[0], cmd, NULL) == -1)
		{
			ft_free_all_arr(paths, cmd);
			perror("exec error");
		}
		exit(1);
	}
	ft_free_all_arr(paths, cmd);
}

int	prompt_shell(char **envp_l)
{
	char	*buffer;
	int		argc;
	char	**argv;

	argv = NULL;
	buffer = readline("Mickeytotal$>");
	while (buffer != NULL)
	{
		argc = 0;
		add_history(buffer);
		argv = parser(buffer, envp_l);
		while (argv[argc])
			argc++;
		if (argc != 0)
		{
			if ((ft_strncmp(argv[0], "echo", 4)) == 0)
				builtin_echo(argv);
			else if ((ft_strncmp(buffer, "pwd", 3)) == 0)
				builtin_pwd();
			else if ((ft_strncmp(buffer, "cd", 2)) == 0)
				builtin_cd(buffer, envp_l);
			else if ((ft_strncmp(buffer, "export", 6)) == 0)
				envp_l = builtin_export(envp_l, argv, argc);
			else if ((ft_strncmp(buffer, "exit", 5)) == 0)
			{
				free(buffer);
				free_2d_arr(argv);
				break ;
			}
			else if ((ft_strncmp(buffer, "env", 3)) == 0)
				builtin_env(envp_l);
			else if (*argv[0])
				exec_cmd(argv, envp_l);
		}
		free_2d_arr(argv);
		free(buffer);
		buffer = NULL;	
		buffer = readline("Mickeytotal$>");
	}
	ft_free_arr(envp_l);
	printf("\nHave a nice day with MickeyTotal \n");
	return (0);
}
