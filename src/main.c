# include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char			**envp_l;
	t_redirections	redirections;
	t_pipes_data	pipes;

	(void)argc;
	(void)argv;
	(void)envp;
	pipes.pipes_detected = FALSE;
	redirections.in_redirection = FALSE;
	redirections.out_redirection = FALSE;
	redirections.infile = NULL;
	redirections.outfile = NULL;
	print_decoration();
	envp_l = copy_envp(envp);
	prompt_shell(envp_l, &redirections, &pipes);
	return (0);
}
