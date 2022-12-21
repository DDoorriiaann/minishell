/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:26:32 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 16:16:42 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_return = 0;

int	main(int argc, char **argv, char **envp)
{
	char			**envp_l;
	t_pipes_data	pipes;

	(void)argc;
	(void)argv;
	(void)envp;
	pipes.pipes_detected = FALSE;
	//print_decoration();
	envp_l = copy_envp(envp);
	prompt_shell(envp_l, &pipes);
	return (g_return);
}
