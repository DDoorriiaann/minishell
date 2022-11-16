#include "minishell.h"

static int	pipe_found_inside(char *arg)
{
	int	i;
	int	input_len_dif;

	input_len_dif = 0;
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '\"')
			i = find_next_corresponding_quote(arg, i + 1, arg[i]);
		if (arg[i] == '|' && arg[i + 1] == '|')
		{
			while (arg[i] == '|')
			{	
				i++;
				input_len_dif--;
			}
		}
		if (arg[i] == '|')
			input_len_dif += 2;
		i++;
	}
	return (input_len_dif);
}

static char	*separate_pipes(char *input, int input_len_dif)
{
	char	*updated_input;
	int		i;
	int		j;
	int		end;

	updated_input = malloc (ft_strlen(input) + input_len_dif + 1);
	i = 0;
	j = 0;
	while (input[i])
	{	
		if (input[i] == '\'' || input[i] == '\"')
		{	
			end = find_next_corresponding_quote(input, i + 1, input[i]);
			while (i < end)
			{
				updated_input[j] = input[i];
				i++;
				j++;
			}
		}
		if (input[i] == '|' && input[i + 1] == '|')
			while (input[i] == '|')
				i++;
		if (input[i] == '|')
		{
			updated_input[j] = ' ';
			j++;
			updated_input[j] = '|';
			j++;
			updated_input[j] = ' ';
		}
		else
			updated_input[j] = input[i];
		i++;
		j++;
	}
	updated_input[j] = '\0';
	return (updated_input);
}

char	*isolate_pipe_symbols(char *input)
{
	int		input_len_dif;
	char	*updated_input;

	input_len_dif = pipe_found_inside(input);
	if (input_len_dif != 0)
		updated_input = separate_pipes(input, input_len_dif);
	else
		updated_input = ft_strdup(input);
	return (updated_input);
}
