/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:29:33 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 14:29:33 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cmd_error(char *cmd)
{	
	if (access(cmd, F_OK) == -1)
	{
		no_such_file_or_directory(cmd);
		return ;
	}
	if (access(cmd, X_OK) == -1)
	{
		permission_denied(cmd);
		return ;
	}
	if (access(cmd, F_OK | X_OK) == 0)
	{
		if ((cmd[0] == '.' && cmd[1] == '/') || cmd[0] == '/')
			is_a_directory(cmd);
		else
			cmd_not_found(cmd);
	}
}

void	ft_error(void)
{
	ft_putstr_fd(" ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}

int	ft_error_return(void)
{
	ft_putstr_fd(" ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	return (1);
}
