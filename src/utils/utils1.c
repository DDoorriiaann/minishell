/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:29:51 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 14:29:52 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	skip_spaces(char *input, int index)
{
	while (ft_isspace(input[index]))
		index++;
	return (index);
}

int	count_splitted_arguments(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}
