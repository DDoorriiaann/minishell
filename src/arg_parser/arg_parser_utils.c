#include "minishell.h"

void	store_arg(char **argv, t_arg_init *arg, int i)
{
	if (arg->end != arg->start)
	{
		argv[i - 1] = ft_substr(arg->input,
				arg->start, (arg->end - arg->start));
		arg->start = arg->end;
	}
	else if (arg->end == arg->start)
		argv[i - 1] = ft_substr(arg->input, arg->start, arg->start + 1);
}

void	store_quoted_arg(char **argv, t_arg_init *arg, int i)
{
	arg->end = go_to_quote_end(arg->input, arg->start, &i);
	argv[i - 1] = ft_substr(arg->input, arg->start + 1,
			(arg->end - (arg->start + 1)));
	arg->start = arg->end;
}
