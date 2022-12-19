#include "minishell.h"

static void	ft_ctrl_c(int sig)
{
	if (sig == SIGINT)
	{
		g_return = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_signal(void)
{
	signal(SIGINT, ft_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_change_signal(__sighandler_t sig)
{
	signal(SIGINT, sig);
	signal(SIGQUIT, sig);
}
