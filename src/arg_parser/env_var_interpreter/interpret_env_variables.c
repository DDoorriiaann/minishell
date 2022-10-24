#include "minishell.h"

static int	skip_lonely_dollars(char *arg, int start)
{
	while (arg[start] == '$' && arg[start] == arg[start + 1])
		start++;
	return (start);
}

static int	skip_single_quoted_content(char *arg, int start)
{
	if (arg[start] == '\''
		&& find_closing_quote(arg, start + 1, arg[start]) != ERROR)
		start = find_closing_quote(arg, start + 1, arg[start]);
	start++;
	return (start);
}

static void	update_argv_with_env_variables(int index, char **argv,
										char **envp, int s_code)
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
		if (arg[start + 1] == '?')
			replace_var_by_status_code(argv, start, index, s_code);
		else if (env_variable_name_exists(arg, start + 1, envp) != ERROR)
			start = interpret_current_env_variable(argv, start, index, envp);
		else
			start = delete_var_inside_arg(argv, start, index);
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

void	interpret_env_variables(char **argv, char **envp, int s_code)
{
	int	i;

	i = 0;
	while (argv[i])
	{	
		update_argv_with_env_variables(i, argv, envp, s_code);
		if (!argv[i][0])
		{	
			remove_arg(argv, i);
			continue ;
		}
		i++;
	}
}
