/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:28:46 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 14:28:47 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_arg(char *argv)
{
	int	i;

	i = 0;
	while (argv[i] && argv[i] != '=' && argv[i] != '+')
		i++;
	if (argv[i] == '=')
		i++;
	return (i);
}
