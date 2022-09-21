#include "minishell.h"

void	echap_last_quote(char *input, char quote_type, int count, int len)
{
	int		i;
	int		j;
	char	*backup;

	backup = ft_strdup(input);
	free(input);
	input = malloc(len + 1);
	input[len + 1] = '\0';
	i = 0;
	j = 0;
	while (backup[i])
	{
		if (backup[i] == quote_type)
		{
			count--;
			if (count == 1)
			{	
				input[j] = '\\';
				j++;
			}
		}
		input[j] = backup[i];
		i++;
		j++;
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

void	check_quotes_pairs(char *input, char quote_type, int len)
{
	int	count;

	count = count_quote_pairs(input, quote_type);
	if (count % 2 != 0)
		echap_last_quote(input, quote_type, count, len);
}

int	parser(char *input)
{
	int	len;

	len = ft_strlen(input);
	check_quotes_pairs(input, len, '\'');
	check_quotes_pairs(input, len, '\"');
}
