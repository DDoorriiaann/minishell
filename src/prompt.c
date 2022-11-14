#include "minishell.h"
#include <stdio.h>
#include <unistd.h>

int	exec_cmd(char **argv, char **envp_l, t_redirections *redirections)
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
	if (pid == 0)
	{
		if (redirections->infile)
		{
			redirections->fd_in = open(redirections->infile, O_RDONLY);
			dup2(redirections->fd_in, STDIN_FILENO);
		}
		if (redirections->outfile)
		{
			dup2(redirections->fd_out, STDOUT_FILENO);
		}
		if (execve(cmd[0], argv, envp_l) == -1)
		{
			ft_free_all_arr(paths, cmd);
			perror("exec error");
		}
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		status_code = WEXITSTATUS(status);
	if (redirections->fd_out)
		close(redirections->fd_out);
	ft_free_all_arr(paths, cmd);
	return (status_code);
}

static char	**builtins(char **argv, char **envp_l, int argc, int *status_code, t_redirections *redirections)
{
	if ((ft_strcmp(argv[0], "echo")) == 0)
		builtin_echo(argv);
	else if ((ft_strcmp(argv[0], "pwd")) == 0)
		builtin_pwd();
	else if ((ft_strcmp(argv[0], "cd")) == 0)
		builtin_cd(argv[0], envp_l);
	else if ((ft_strcmp(argv[0], "export")) == 0)
		envp_l = builtin_export(envp_l, argv, argc);
	else if ((ft_strcmp(argv[0], "exit")) == 0)
		builtin_exit(argv, *status_code, envp_l);
	else if ((ft_strcmp(argv[0], "env")) == 0)
		builtin_env(envp_l);
	else if ((ft_strcmp(argv[0], "unset")) == 0)
		envp_l = builtin_unset(envp_l, argv);
	else if (*argv[0])
		*status_code = exec_cmd(argv, envp_l, redirections);
	return (envp_l);
}

int	prompt_shell(char **envp_l, t_redirections *redirections,
		t_pipes_data *pipes)
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
		argv = arg_parser(buffer, envp_l, status_code, redirections);
		free(buffer);
		buffer = NULL;
		while (argv[argc])
			argc++;
		if (argc != 0)
			envp_l = builtins(argv, envp_l, argc, &status_code, redirections);
		free_2d_arr(argv);
		reset_redirections(redirections);
		buffer = readline("Mickeytotal$>");
	}
	free_2d_arr(envp_l);
	printf("\nHave a nice day with MickeyTotal \n");
	return (0);
}
