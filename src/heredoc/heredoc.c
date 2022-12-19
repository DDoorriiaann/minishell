#include "minishell.h"
#include <readline/readline.h>

int	create_heredoc_path(t_redirections *redirections)
{
	if (redirections->here_doc_path)
		free(redirections->here_doc_path);
	redirections->here_doc_path = ft_strjoin("./here_doc", ft_itoa(redirections->fork_index));
	if (!redirections->here_doc_path)
		return (ERROR);
	else
		return (0);
}

void	delete_heredoc(t_fork *cur_fork)
{	
	close(cur_fork->redirections->here_doc);
	unlink(cur_fork->redirections->here_doc_path);
	free(cur_fork->redirections->here_doc_path);
}

////GET HEREDOC/////////
void signal_handler(int signum)
{
  printf("Received signal %d\n", signum);
}
static void	set_heredoc(char *delimiter, int heredoc_fd)
{
	char	*line;
	struct sigaction sa;
	
	sigemptyset(&sa.sa_mask);	
	sa.sa_flags = 0;
 	sa.sa_handler = signal_handler;	
	sigaction(SIGINT, &sa, NULL);
	line = readline("> ");
	
	while (line && strcmp(line, delimiter))
	{
	//	ft_signal();
		//interpret env variables
		ft_putstr_fd(line, heredoc_fd);
		write(heredoc_fd, "\n", 1);
		line = readline("> ");
	}
}



////////////////////////

void	wait_heredoc(int	pid)
{
	waitpid(pid, &g_return, 0);
	if (g_return == 2)
	{
		printf("\n");
		g_return = 130;
	}
	else if (g_return == 131)
		printf("Quit (core dumped)\n");
	else
		g_return = WEXITSTATUS(g_return);
}

void	ft_heredoc(t_fork *cur_fork)
{
	int	pid;

	cur_fork->redirections->here_doc = open(cur_fork->redirections->here_doc_path, O_CREAT | O_RDWR | O_APPEND, 0644);
	pid = fork();
	if (pid == -1)
		perror("fork error");
	if (pid == 0)
		set_heredoc(cur_fork->redirections->delimiter, cur_fork->redirections->here_doc);
	else
		wait_heredoc(pid);
	close(cur_fork->redirections->here_doc);
}
