# include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	
	(void)argc;
	(void)argv;
	(void)envp;
	prompt_shell(envp);
	return (0);
}
