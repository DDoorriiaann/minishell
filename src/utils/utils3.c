/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:29:56 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 14:29:57 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_next_corresponding_quote(char *input, int end, char quote_type)
{
	while (input[end])
	{
		if (input[end] == quote_type)
			return (end);
		end++;
	}
	return (ERROR);
}

char	**delete_argument(char **argv, int arg_index, int args_to_delete)
{
	int		argc;
	char	**updated_argv;
	int		i;

	argc = count_splitted_arguments(argv);
	updated_argv = malloc(sizeof(char *) * argc - args_to_delete + 1);
	i = 0;
	while (i < arg_index)
	{
		updated_argv[i] = ft_strdup(argv[i]);
		i++;
	}
	while (argv[i + args_to_delete])
	{
		updated_argv[i] = ft_strdup(argv[i + args_to_delete]);
		i++;
	}
	updated_argv[i] = NULL;
	free_2d_arr(argv);
	return (updated_argv);
}

void	dup_arr(char **src, char **dst)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dst[i] = ft_strdup(src[i]);
		i++;
	}
	dst[i] = NULL;
}
