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

int	prompt_shell(char **envp_l)
{
	char	*buffer;
	int		argc;
	char	**argv;
	int		i;

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
    add_history(buffer);
		argv = parser(buffer);
    while (argv[argc])
      argc++;
		i = 0;
		
		if ((ft_strncmp(buffer, "echo", 4)) == 0)
			builtin_echo(buffer);
		else if ((ft_strncmp(buffer, "pwd", 3)) == 0)
			builtin_pwd();
		else if ((ft_strncmp(buffer, "cd", 2)) == 0)
//		{
			builtin_cd(buffer, envp_l);
//			while (envp_l[i] != NULL)
//			{
//				printf("%s\n", envp_l[i]);
//				i++;
//			}
//		}
		else
			exec_cmd(buffer, envp_l);
    free_2d_arr(argv);
		free(buffer);
		buffer = NULL;
	}
	printf("\nHave a nice day with MickeyTotal \n");
	return (0);
}
