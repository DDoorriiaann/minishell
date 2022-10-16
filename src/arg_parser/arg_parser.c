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

char	**split_input(char *input, int argc)
{
	char	**argv;

	argv = init_argv(argc);
	put_args_into_argv(argv, input);
	return (argv);
}

char	**arg_parser(char *input, char **envp, int e_code)
{
	int		argc;
	char	**argv;

	argc = count_arguments(input, 0);
	argv = split_input(input, argc);
	interpret_env_variables(argv, envp, e_code);
	return (argv);
}
