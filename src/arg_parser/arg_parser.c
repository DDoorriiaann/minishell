#include "minishell.h"

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
		else if (end == start)
			argv[i - 1] = ft_substr(input, start, start + 1);
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

char	**raw_input_parser(char *input)
{
	int		argc;
	char	**argv;
	char	*updated_input;

	updated_input = isolate_pipe_symbols(input);
	argc = count_arguments(updated_input, 0);
	argv = split_input(updated_input, argc);
	free(updated_input);
	return (argv);
}
