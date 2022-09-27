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

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == 32)
		return (1);
	return (0);
}

int	ft_is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (1);
	return (0);
}

int	skip_spaces(char *input, int index)
{
	while (ft_isspace(input[index]))
		index++;
	return (index);
}

int	find_word_end(char *input, int index)
{
	while (input[index] && !ft_isspace(input[index]) && !ft_is_quote(input[index]))
		index++;
	return (index);
}

int go_to_word_end(char *input, int index, int *argc)
{
	if (input[index] && !ft_isspace(input[index]) && !ft_is_quote(input[index]))
	{
		*argc = *argc + 1;
		index = find_word_end(input, index);
	}
	return (index);
}

int	count_arguments(char *input)
{
	int	end;
	int	argc;

	argc = 0;
	end = 0;
	end = skip_spaces(input, end);
	while (input[end])
	{
		end = go_to_word_end(input, end, &argc);
		if (ft_isspace(input[end]))
		{	
			end = skip_spaces(input, end);
			continue ;
		}
		else if (ft_is_quote(input[end]))
		{
			if (find_closing_quote(input, end + 1, input[end]) != ERROR)
			{
				end = find_closing_quote(input, end + 1, input[end]);
				argc++;
			}
			else if (ft_isspace(input[end + 1]) || !input[end + 1])
				argc++;
		}
		end++;
	}
	return (argc);
}

int	parser(char *input)
{
	int		argc;
//	char	**args;

	argc = count_arguments(input);
	return (argc);
	//args = malloc (sizeof(char *) * (args_count + 1));
	//args = split_input(input, start);
}
