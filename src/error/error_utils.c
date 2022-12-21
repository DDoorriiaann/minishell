/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:29:35 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 14:29:35 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_not_found(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found", 2);
	ft_putstr_fd("\n", 2);
	g_return = 127;
}

void	is_a_directory(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": Is a directory", 2);
	ft_putstr_fd("\n", 2);
	g_return = 126;
}

void	no_such_file_or_directory(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": No such file or directory", 2);
	ft_putstr_fd("\n", 2);
	g_return = 127;
}

void	permission_denied(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": Permission denied", 2);
	ft_putstr_fd("\n", 2);
	g_return = 126;
}
