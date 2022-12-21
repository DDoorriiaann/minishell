/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpret_env_variables.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:23:55 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 14:23:56 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_lonely_dollars(char *arg, int start)
{
	while (arg[start] == '$' && arg[start] == arg[start + 1])
		start++;
	return (start);
}

static int	interpret_variable(char **argv, int index, int *start, char **envp)
{
	char	*arg;

	arg = argv[index];
	if (arg[*start + 1] == '?')
		replace_var_by_status_code(argv, *start, index);
	else if (env_variable_name_exists(arg, *start + 1, envp) != ERROR)
		*start = interpret_current_env_variable(argv, *start, index, envp);
	else if (arg[*start] == '$' && (!arg[*start + 1] || arg[*start + 1] == ' '
			|| ft_is_quote(arg[*start + 1])))
	{
		*start = *start + 1;
		return (TRUE);
	}
	else
		*start = delete_var_inside_arg(argv, *start, index);
	return (FALSE);
}

static void	update_argv_with_env_variables(int index, char **argv,
										char **envp)
{
	int		start;
	char	*arg;

	arg = argv[index];
	start = 0;
	while (arg[start])
	{
		if (arg[start] == '$' && arg[start + 1] == '$')
			start = skip_lonely_dollars(arg, start);
		if (arg[start] != '$' || !arg[start + 1] || ft_isspace(arg[start + 1]))
		{
			start = skip_single_quoted_content(arg, start);
			continue ;
		}
		if (interpret_variable(argv, index, &start, envp) == TRUE)
			continue ;
		arg = argv[index];
		start++;
	}
}

static void	remove_arg(char **argv, int i)
{
	while (argv[i + 1])
	{
		free(argv[i]);
		argv[i] = ft_strdup(argv[i + 1]);
		i++;
	}
	free(argv[i]);
	argv[i] = NULL;
}

void	interpret_env_variables(char **argv, char **envp)
{
	int	i;

	i = 0;
	while (argv[i])
	{	
		update_argv_with_env_variables(i, argv, envp);
		if (!argv[i][0])
		{	
			remove_arg(argv, i);
			continue ;
		}
		i++;
	}
}
