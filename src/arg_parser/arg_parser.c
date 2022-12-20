#include "minishell.h"

static int	count_arguments(char *input, int argc)
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

static char	**init_argv(int argc)
{
	char	**argv;

	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return (NULL);
	argv[argc] = NULL;
	return (argv);
}

static void	put_args_into_argv(char **argv, char *input)
{
	int			i;
	t_arg_init	arg;

	i = 0;
	arg.input = input;
	arg.start = 0;
	arg.start = skip_spaces(input, arg.start);
	while (arg.start < (int)ft_strlen(input))
	{
		arg.end = go_to_word_end(arg.input, arg.start, &i);
		store_arg(argv, &arg, i);
		if (ft_isspace(arg.input[arg.start]))
		{
			arg.end = skip_spaces(arg.input, arg.start);
			arg.start = arg.end;
			continue ;
		}
		else if (ft_is_quote(arg.input[arg.start]))
			store_quoted_arg(argv, &arg, i);
		arg.start++;
	}
}

static char	**split_input(char *input, int argc)
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
