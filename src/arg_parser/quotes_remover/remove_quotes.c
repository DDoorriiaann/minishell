#include "minishell.h"

static int	backup_arg_part(t_arg_update *update, int backup_start,
		int end, int cur_index)
{
	while (cur_index < end)
	{
		update->updated_arg[backup_start] = update->original_arg[cur_index];
		cur_index++;
		backup_start++;
	}
	return (backup_start);
}

static void	delete_quotes_from_arg(char **argv, int arg_index,
		int quote_start, int quote_end)
{
	t_arg_update	*update;
	int				new_arg_len;
	int				original_arg_len;
	int				backup_start;

	update = malloc(sizeof(t_arg_update));
	original_arg_len = ft_strlen(argv[arg_index]);
	new_arg_len = original_arg_len - 2;
	update->updated_arg = malloc(new_arg_len + 1);
	update->original_arg = argv[arg_index];
	backup_start = backup_arg_part(update, 0, quote_start, 0);
	backup_start = backup_arg_part(update, backup_start,
			quote_end, quote_start + 1);
	backup_start = backup_arg_part(update, backup_start,
			original_arg_len, quote_end + 1);
	update->updated_arg[new_arg_len] = '\0';
	free(argv[arg_index]);
	argv[arg_index] = update->updated_arg;
	free(update);
}

static int	handle_quotes(char **argv, int arg_index, int cur_char)
{
	int		quote_start;
	int		quote_end;
	char	*arg;

	arg = argv[arg_index];
	quote_start = cur_char;
	quote_end = find_next_corresponding_quote(arg, cur_char + 1, arg[cur_char]);
	if (quote_end != ERROR)
	{	
		delete_quotes_from_arg(argv, arg_index, quote_start, quote_end);
		return (quote_end - 2);
	}
	else
		return (cur_char);
}

char	*remove_quotes_in_filename(char *filename)
{
	int		i;
	char	**wrapper;
	char	*updated_filename;

	wrapper = malloc(sizeof(char *));
	wrapper[0] = filename;
	i = 0;
	while (wrapper[0][i])
	{
		if (ft_is_quote(wrapper[0][i]))
			i = handle_quotes(wrapper, 0, i) - 1;
		i++;
	}
	updated_filename = wrapper[0];
	free(wrapper);
	return (updated_filename);
}

void	remove_quotes(char **argv)
{
	int		i;
	int		arg_index;

	arg_index = 0;
	while (argv[arg_index])
	{
		i = 0;
		while (argv[arg_index][i])
		{
			if (ft_is_quote(argv[arg_index][i]))
				i = handle_quotes(argv, arg_index, i);
			i++;
		}
		arg_index++;
	}
}
