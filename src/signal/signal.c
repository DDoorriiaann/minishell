/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:29:48 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 14:29:49 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	ft_ctrl_c_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		g_return = 130;
		close(0);
	}
}

void	ft_signal(void)
{
	signal(SIGINT, ft_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_signal_heredoc(void)
{
	signal(SIGINT, ft_ctrl_c_heredoc);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_change_signal(__sighandler_t sig)
{
	signal(SIGINT, sig);
	signal(SIGQUIT, sig);
}
