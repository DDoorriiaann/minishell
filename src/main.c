# include "minishell.h"

int main(int argc, char **argv, char **envp)
{
	char			**envp_l;
	t_redirections	redirections;

	(void)argc;
	(void)argv;
	(void)envp;
	redirections.in_redirection = FALSE;
	redirections.out_redirection = FALSE;
	redirections.infile = NULL;
	print_decoration();
	envp_l = copy_envp(envp);
	prompt_shell(envp_l, &redirections);
	return (0);
}
