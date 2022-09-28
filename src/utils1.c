#include "minishell.h"

void	free_2d_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
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
	while (input[index]
		&& !ft_isspace(input[index]) && !ft_is_quote(input[index]))
		index++;
	return (index);
}
