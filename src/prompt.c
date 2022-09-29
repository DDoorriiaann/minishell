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
			perror("exec error");
		exit(1);
	}
}

int	prompt_shell(char **envp)
{
	char	*buffer;
	int		argc;
	char	**argv;

	(void)envp;
//	size_t	buf_size;

//	buf_size = 2048;
	/*buffer = (char *)malloc(sizeof(char) * buf_size);
	if (!buffer)
	{
		perror("Malloc failure");
		return (1);
	}*/
	argv = NULL;
	while ((buffer = readline("Mickeytotal$>")) != NULL)
	{
		argc = 0;
		argv = parser(buffer);
		while (argv[argc])
			printf("%s\n", argv[argc++]);
		printf("argc = %d\n", argc);
		free_2d_arr(argv);
		add_history(buffer);
		if ((ft_strncmp(buffer, "echo", 4)) == 0)
			builtin_echo(buffer);
		else
			exec_cmd(buffer, envp);
		free(buffer);
		buffer = NULL;
	}
	printf("\nHave a nice day with MickeyTotal \n");
	return (0);
}
