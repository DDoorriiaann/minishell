/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybaudoui <ybaudoui@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:35:09 by ybaudoui          #+#    #+#             */
/*   Updated: 2022/09/30 17:35:25 by ybaudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_env(char **envp_l)
{
	int	i;

	i = 0;
	while (envp_l[i])
		i++;
	return (i);
}

int	sort_ascii(char **envp_l, int ret, int i)
{
	char	*tmp;

	ret = size_env(envp_l);
	tmp = ft_strdup(envp_l[i]);
	free(envp_l[i]);
	envp_l[i] = envp_l[i + 1];
	envp_l[i + 1] = tmp;
	return (ret);
}

void	sort_first_char(char **envp_l)
{
	int	i;
	int	j;
	int	ret;

	j = 0;
	ret = size_env(envp_l);
	while (ret != 0)
	{
		i = 0;
		while (envp_l[i] && envp_l[i + 1])
		{
			if (envp_l[i][j] > envp_l[i + 1][j])
				ret = sort_ascii(envp_l, ret, i);
			i++;
		}
		ret--;
	}
}

void	sort_after_first_char(char **envp_l)
{
	int	i;
	int	j;
	int	ret;

	ret = size_env(envp_l);
	while (ret != 0)
	{
		i = 0;
		while (envp_l[i] && envp_l[i + 1])
		{
			j = 0;
			while (envp_l[i][j] == envp_l[i + 1][j])
			{
				j++;
				if (envp_l[i][j] > envp_l[i + 1][j])
					ret = sort_ascii(envp_l, ret, i);
			}
			i++;
		}
		ret--;
	}
}

void	builtin_export(char **envp_l, char **argv, int argc)
{
	char	**copy_envp_l;

	copy_envp_l = copy_envp(envp_l);
	sort_first_char(copy_envp_l);
	sort_after_first_char(copy_envp_l);
	if (argc == 1)
		print_export(copy_envp_l);
	else
		add_arg_export(copy_envp_l, argv, argc);
//	ft_free_arr(copy_envp_l);
}

void	print_export(char **copy_envp_l)
{
	int		i;
	char	*tmp;

	i = 0;
	while (copy_envp_l[i])
	{
		if (copy_envp_l[i][0] != '_')
		{
			tmp = ft_strjoin("declare -x ", copy_envp_l[i]);
			printf("%s\n", tmp);
			free(tmp);
		}
		i++;
	}
}

void	add_arg_export(char **copy_envp_l, char **argv, int argc)
{
	char	**tmp_envp_l;
	int		i;
	int		j;

	i = 0;
	tmp_envp_l = malloc(sizeof(char *) * size_env(copy_envp_l) + argc);
	while (copy_envp_l[i])
	{
		tmp_envp_l[i] = strdup(copy_envp_l[i]);
		i++;
	}
	j = 1;
	while (argv[j])
	{
		tmp_envp_l[i] = argv[j];
		j++;
		i++;
	}
	tmp_envp_l[i] = NULL;
}
