#include "minishell.h"

void	exec_cmd(char *argv, char **envp_l)
{
	int		pid = 0;
	int		status = 0;
	char	**paths;
	char	**cmd;

	paths = get_path(check_line_path(envp_l));
	cmd = get_cmd(argv, paths);
	if (!cmd)
		ft_free_arr(paths);
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
		argv = parser(buffer);
		while (argv[argc])
			argc++;
		if ((ft_strncmp(buffer, "echo", 4)) == 0)
			builtin_echo(buffer);
		else if ((ft_strncmp(buffer, "pwd", 3)) == 0)
			builtin_pwd();
		else if ((ft_strncmp(buffer, "cd", 2)) == 0)
			builtin_cd(buffer, envp_l);
		else if ((ft_strncmp(buffer, "export", 6)) == 0)
			envp_l = builtin_export(envp_l, argv, argc);
		else if ((ft_strncmp(buffer, "env", 3)) == 0)
			builtin_env(envp_l);
		else if ((ft_strncmp(buffer, "exit", 5)) == 0)
		{
			free(buffer);
			free_2d_arr(argv);
			break ;
		}
		else if (buffer[0])
			exec_cmd(buffer, envp_l);
		free_2d_arr(argv);
		free(buffer);
		buffer = NULL;	
		buffer = readline("Mickeytotal$>");
	}
	ft_free_arr(envp_l);
	printf("\nHave a nice day with MickeyTotal \n");
	return (0);
}
