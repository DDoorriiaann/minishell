#include "minishell.h"
/*
void	echap_last_quote(char *input, char quote_type, int count)
{
	int		i;

	i = 0;
	while (input[i])
	{
		if (input[i] == quote_type)
		{
			count--;
			if (count == 0)
			{	
				input[i] = quote_type;
			}
		}
		i++;
	}
}

int	count_quote_pairs(char *input, char quote_type)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (input [i])
	{
		if (input[i] == quote_type)
			count++;
		i++;
	}
	return (count);
}

void	check_quotes_pairs(char *input, char quote_type)
{
	int	count;

	count = count_quote_pairs(input, quote_type);
	if (count % 2 != 0)
		echap_last_quote(input, quote_type, count);
}
*/

int	count_arguments(char *input, int argc)
{
	int	end;
	int	input_len;

	end = 0;
	end = skip_spaces(input, end);
	input_len = ft_strlen(input);
	while (end < (int)input_len)
	{
		end = go_to_word_end(input, end, &argc);
		if (ft_isspace(input[end]))
		{
			end = skip_spaces(input, end);
			continue ;
		}
		else if (ft_is_quote(input[end]))
			end = go_to_quote_end(input, end, &argc);
		end++;
	}
	return (argc);
}

char	**init_argv(int argc)
{
	char	**argv;

	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return (NULL);
	argv[argc] = NULL;
	return (argv);
}

void	put_args_into_argv(char **argv, char *input)
{
	int	i;
	int	start;	
	int	end;

	i = 0;
	start = 0;
	start = skip_spaces(input, start);
	while (start < (int)ft_strlen(input))
	{
		end = go_to_word_end(input, start, &i);
		if (end != start)
		{
			argv[i - 1] = ft_substr(input, start, (end - start));
			start = end;
		}
		if (ft_isspace(input[start]))
		{
			end = skip_spaces(input, start);
			start = end;
			continue ;
		}
		else if (ft_is_quote(input[start]))
		{
			end = go_to_quote_end(input, start, &i);
			argv[i - 1] = ft_substr(input, start + 1, (end - (start + 1)));
			start = end;
		}
		start++;
	}
}

char	*extract_env_variable_name(char *arg, int start)
{
	int		end;
	char	*env_variable_name;
	int		i;

	end = start;
	while (arg[end] && (ft_isalnum(arg[end]) || arg[end] == '_'))
		end++;
	env_variable_name = malloc((end - start) + 2);
	i = 0;
	while (start < end)
	{
		env_variable_name[i] = arg[start];
		start++;
		i++;
	}
	env_variable_name[i] = '=';
	env_variable_name[i + 1] = '\0';
	return (env_variable_name);
}

int	variable_found_inside_env(char *env_variable_name, char **envp)
{
	int	i;
	int	len;

	len = ft_strlen(env_variable_name);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], env_variable_name, len) == 0)
			return (i);
		i++;
	}
	return (FALSE);
}

int	env_variable_name_exists(char *arg, int start, char **envp)
{
	char	*env_variable_name;
	int		variable_index;

	env_variable_name = extract_env_variable_name(arg, start);
	variable_index = variable_found_inside_env(env_variable_name, envp);
	if (variable_index)
		return (variable_index);
	else
		return (ERROR);
}

void	replace_variable_by_content(char **argv, int index, int start, t_env_var var)
{
	char	*updated_arg;
	int		i;

	i = 0;
	updated_arg = malloc(var.len - (ft_strlen(var.name)) + 1);
	updated_arg[var.len - ft_strlen(var.name)] = '\0';
	while (i < start)
	{
		updated_arg[i] = argv[index][i];
		i++;
	}
	while (*var.value)
	{
		updated_arg[i] = *var.value;
		var.value++;
		i++;
	}
	start = start + ft_strlen(var.name);
	while (argv[index][start])
	{
		updated_arg[i] = argv[index][start];
		start++;
		i++;
	}
	free(argv[index]);
	argv[index] = updated_arg;
}

int	replace_env_variable_name_with_content(char **argv, int start, int arg_index, char **envp)
{
//	char	*tmp;
	t_env_var	var;
	int	value_start;

	var.index = env_variable_name_exists(argv[arg_index], start + 1, envp);
	var.len = (int)ft_strlen(envp[var.index]);
	var.name = extract_env_variable_name(argv[arg_index], start + 1);
	value_start = ft_strlen(var.name);
	var.value = ft_substr(envp[var.index], value_start, var.len - value_start);
	replace_variable_by_content(argv, arg_index, start, var);
	return (start + ft_strlen(var.name));
}

void	update_argv_with_env_variables(int index, char **argv, char **envp)
{
	int		start;
	char	*arg;

	arg = argv[index];
	start = 0;
	while (arg[start])
	{
		if (arg[start] == '$')
		{	
			if (!arg[start + 1] || ft_isspace(arg[start + 1]))
			{
				start++;
				continue ;
			}
			else if (env_variable_name_exists(arg, start + 1, envp) != ERROR)
				start = replace_env_variable_name_with_content(argv, start, index, envp);
			//else
				//i = delete_env_variable_name_from_string(arg, i, envp);
		}
		start++;
	}
}

void	interpret_env_variables(char **argv, char **envp)
{
	int	i;

	i = 0;
	while (argv[i])
	{	
		update_argv_with_env_variables(i, argv, envp);
		i++;
	}
}

char	**split_input(char *input, int argc)
{
	char	**argv;

	argv = init_argv(argc);
	put_args_into_argv(argv, input);
	return (argv);
}

char	**parser(char *input, char **envp)
{
	int		argc;
	char	**argv;

	argc = count_arguments(input, 0);
	argv = split_input(input, argc);
	interpret_env_variables(argv, envp);
	return (argv);
}
