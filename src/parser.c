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
int	find_closing_quote(char *input, int end, char quote_type)
{
	while (input[end])
	{
		if (input[end] == quote_type)
			return (end);
		end++;
	}
	return (ERROR);
}

int	go_to_word_end(char *input, int index, int *argc)
{
	if (input[index] && !ft_isspace(input[index]) && !ft_is_quote(input[index]))
	{
		*argc = *argc + 1;
		index = find_word_end(input, index);
	}
	return (index);
}

int	go_to_quote_end(char *input, int index, int *argc)
{
	if (find_closing_quote(input, index + 1, input[index]) != ERROR)
	{
		index = find_closing_quote(input, index + 1, input[index]);
		*argc = *argc + 1;
	}
	else if (ft_isspace(input[index + 1]) || !input[index + 1])
		*argc = *argc + 1;
	return (index);
}

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

void	split_word(char *input, char **argv,)

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
			argv[i - 1] = ft_substr(input, start, (end - start) + 1);
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

char	**parser(char *input)
{
	int		argc;
	char 	**argv;

	argc = count_arguments(input, 0);
	argv = split_input(input, argc);
	return (argv);
	//args = malloc (sizeof(char *) * (args_count + 1));
	//args = split_input(input, start);
}
