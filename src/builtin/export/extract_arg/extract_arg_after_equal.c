/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_arg_after_equal.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:28:38 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 14:28:39 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_arg_after_equal(char *argv)
{
	char	*new_arg;
	int		start;
	int		len;

	start = size_arg_before_equal(argv);
	len = size_arg(argv);
	new_arg = ft_substr(argv, start + 1, len);
	return (new_arg);
}
