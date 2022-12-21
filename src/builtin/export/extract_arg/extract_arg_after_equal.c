#include "minishell.h"

char	*extract_arg_after_equal(char *argv)
{
	char	*new_arg;
	int		start;
	int		len;

	start = size_arg_before_equal(argv);
	len = size_arg(argv);
	new_arg = ft_substr(argv, start + 1, len);
	return (new_arg);
}
