/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_envp_l.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:29:06 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 14:29:07 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_variable(char **envp_l, char *var, int index)
{
	free(envp_l[index]);
	envp_l[index] = ft_strdup(var);
}

static char	*remove_plus(char*argv)
{
	int		i;

	i = 0;
	while (argv[i] != '+')
		i++;
	while (argv[i])
	{
		argv[i] = argv[i + 1];
		i++;
	}
	return (argv);
}

static void	join_variable(char **envp_l, char *var, int index)
{
	char	*tmp;
	int		i;

	i = 0;
	while (envp_l[index][i])
	{
		if (envp_l[index][i] == '=')
		{
			var = extract_arg_after_equal(var);
			break ;
		}
		i++;
	}
	if (envp_l[index][i] != '=')
		var = extract_arg_with_equal(var);
	tmp = ft_strdup(envp_l[index]);
	free(envp_l[index]);
	envp_l[index] = ft_strjoin(tmp, var);
	free(tmp);
	free(var);
}

static void	existing_export(char **argv, char **envp_l, int var_index, int i)
{
	if (check_char_equal(argv[i]) == 1)
		update_variable(envp_l, argv[i], var_index);
	if (check_char_equal(argv[i]) == 2)
		join_variable(envp_l, argv[i], var_index);
}

void	update_envp_l(char **argv, char **envp_l)
{
	int		len;
	int		i;
	int		var_index;

	len = 0;
	while (envp_l[len])
		len++;
	i = 1;
	while (argv[i])
	{
		if (!(argv[i][0] == '_' && argv[i][1] == '='))
		{
			var_index = check_arg(envp_l, argv[i]);
			if (var_index != -1)
				existing_export(argv, envp_l, var_index, i);
			else if (check_syntax(argv[i]) == TRUE)
			{
				if (check_plus(argv[i]) == TRUE)
					argv[i] = remove_plus(argv[i]);
				envp_l[len++] = ft_strdup(argv[i]);
				envp_l[len] = NULL;
			}
		}
		i++;
	}
}
