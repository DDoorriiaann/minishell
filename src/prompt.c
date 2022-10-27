#include "minishell.h"
#include <stdio.h>

int	exec_cmd(char **argv, char **envp_l)
{
	int		pid = 0;
	int		status = 0;
	char	**paths;
	char	**cmd;
	int		status_code;

	status_code = 0;
	if (!argv[0])
		return (EXIT_FAILURE);
	paths = get_path(check_line_path(envp_l));
	cmd = get_cmd(argv[0], paths);
	if (!cmd)
	{
		free_2d_arr(paths);
		ft_error_cmd(argv[0]);
		return (127);
	}
	pid = fork();
	if (pid == -1)
		perror("fork error");
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			status_code = WEXITSTATUS(status);
		}
	}
	else
	{
		if (execve(cmd[0], cmd, envp_l) == -1)
		{
			ft_free_all_arr(paths, cmd);
			perror("exec error");
		}
		exit(EXIT_FAILURE);
	}
	ft_free_all_arr(paths, cmd);
	return (status_code);
}

int	prompt_shell(char **envp_l)
{
	char	*buffer;
	int		argc;
	char	**argv;
	int		status_code;

	argv = NULL;
	status_code = 0;
	buffer = readline("Mickeytotal$>");
	while (buffer != NULL)
	{
		argc = 0;
		add_history(buffer);
		argv = arg_parser(buffer, envp_l, status_code);
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
			else if ((ft_strncmp(buffer, "unset", 5)) == 0)
				envp_l = builtin_unset(envp_l, argv);
			else if (*argv[0])
				status_code = exec_cmd(argv, envp_l);
		}
		free_2d_arr(argv);
		argv = NULL;
		free(buffer);
		buffer = NULL;
		buffer = readline("Mickeytotal$>");
	}
	free_2d_arr(envp_l);
	printf("\nHave a nice day with MickeyTotal \n");
	return (0);
}
