/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybaudoui <ybaudoui@student.42angoulem      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:35:09 by ybaudoui          #+#    #+#             */
/*   Updated: 2022/10/04 12:43:25 by ybaudoui         ###   ########.fr       */
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

char	**builtin_export(char **envp_l, char **argv, int argc)
{
	char	**export_envp_l;

	export_envp_l = copy_envp(envp_l);
	sort_first_char(export_envp_l);
	sort_after_first_char(export_envp_l);
	if (argc == 1)
		print_export(export_envp_l);
	else
		envp_l = add_arg_export(envp_l, argv, argc);
	free_2d_arr(export_envp_l);
	printf("%d\n", size_env(envp_l));
	return (envp_l);
}

void	print_export(char **export_envp_l)
{
	int		i;
	char	*tmp;

	i = 0;
	while (export_envp_l[i])
	{
		if (export_envp_l[i][0] != '_')
		{
			tmp = ft_strjoin("declare -x ", export_envp_l[i]);
			printf("%s\n", tmp);
			free(tmp);
		}
		i++;
	}
}

char	**add_arg_export(char **envp_l, char **argv, int argc)
{
	char	**tmp_envp_l;
	int		i;
	int		j;

	i = 0;
	tmp_envp_l = malloc(sizeof(char *) * (size_env(envp_l) + (argc)));
	while (envp_l[i])
	{
		tmp_envp_l[i] = ft_strdup(envp_l[i]);
		i++;
	}
	j = 1;
	while (argv[j])
	{
		tmp_envp_l[i] = ft_strdup(argv[j]);
		printf("%s\n", tmp_envp_l[i]);
		j++;
		i++;
	}
	tmp_envp_l[i] = NULL;
	printf("i = %d\n", i);
	printf("%s\n",tmp_envp_l[i - 1]);
	free_2d_arr(envp_l);
	return (tmp_envp_l);
}
