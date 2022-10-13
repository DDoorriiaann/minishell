#include "minishell.h"

char	**builtin_export(char **envp_l, char **argv, int argc)
{
	char	**export_envp_l;

	export_envp_l = copy_envp(envp_l);
	sort_first_char(export_envp_l);
	sort_after_first_char(export_envp_l);
	if (argc == 1)
		print_export(export_envp_l);
	else
		envp_l = add_arg_export(envp_l, argv);
	free_2d_arr(export_envp_l);
	return (envp_l);
}

void	print_export(char **export_envp_l)
{
	int		i;
	int		j;

	i = 0;
	while (export_envp_l[i])
	{
		if (export_envp_l[i][0] == '_')
		{
			i++;
			continue ;
		}
		j = 0;
		ft_putstr_fd("declare -x ", 1);
		while (export_envp_l[i][j] && export_envp_l[i][j] != '=')
		{
			ft_putchar_fd(export_envp_l[i][j], 1);
			j++;
		}
		if (export_envp_l[i][j])
		{
			ft_putchar_fd(export_envp_l[i][j], 1);
			ft_putchar_fd('\"', 1);
			while (export_envp_l[i][++j])
				ft_putchar_fd(export_envp_l[i][j], 1);
			ft_putchar_fd('\"', 1);
		}
		ft_putchar_fd('\n', 1);
		i++;
	}
}

char	**add_arg_export(char **envp_l, char **argv)
{
	char	**tmp_envp_l;
	int		new_vars;

	new_vars = check_if_new_variables(argv, envp_l);
	if (new_vars)
	{
		tmp_envp_l = malloc(sizeof(char *)
				* (size_env(envp_l) + ((new_vars) + 1)));
		dup_arr(envp_l, tmp_envp_l);
		tmp_envp_l[size_env(envp_l) + new_vars] = NULL;
		update_envp_l(argv, tmp_envp_l);
		free_2d_arr(envp_l);
	}
	else
	{
		update_envp_l(argv, envp_l);
		tmp_envp_l = envp_l;
	}
	return (tmp_envp_l);
}
