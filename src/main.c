# include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	char	**envp_l;

	(void)argc;
	(void)argv;
	(void)envp;
	print_decoration();
	envp_l = copy_envp(envp);
	prompt_shell(envp_l);
	return (0);
}
