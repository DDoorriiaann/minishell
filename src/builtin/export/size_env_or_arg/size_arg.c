/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_arg.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:28:48 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 14:28:49 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_arg(char *argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}
