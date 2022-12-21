/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_dollars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:28:26 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 14:28:27 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_char_before_equal(char *argv)
{
	int	j;

	j = 0;
	while (argv[j] != '=' && argv[j])
		j++;
	return (j);
}

static int	count_dollars(char *arg)
{
	int	j;
	int	count;

	count = 0;
	j = skip_char_before_equal(arg);
	while (arg[j])
	{
		if (arg[j] == '$')
			count++;
		j++;
	}
	return (count);
}

static char	*insert_backslash(char *new_arg, char *arg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arg[i])
	{
		if (arg[i] == '$')
		{
			new_arg[j] = '\\';
			j++;
		}
		new_arg[j] = arg[i];
		i++;
		j++;
	}
	new_arg[j] = '\0';
	return (new_arg);
}

char	**check_dollars(char **argv)
{
	int		i;
	int		count;
	char	*new_argv;

	i = 1;
	while (argv[i])
	{
		count = count_dollars(argv[i]);
		if (count != 0)
		{
			new_argv = malloc(sizeof(char) * (ft_strlen(argv[i]) + count + 1));
			new_argv = insert_backslash(new_argv, argv[i]);
			free(argv[i]);
			argv[i] = new_argv;
		}
		i++;
	}
	return (argv);
}
