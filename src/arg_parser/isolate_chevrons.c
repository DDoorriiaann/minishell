/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isolate_chevrons.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:06:17 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 17:12:51 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_chevrons_by_type(char *arg, int input_len_dif, char chevron_type)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] == '\'' || arg[i] == '\"')
			i = find_next_corresponding_quote(arg, i + 1, arg[i]);
		if (arg[i] == chevron_type)
			input_len_dif += 2;
		if (arg[i] == chevron_type && arg[i + 1] == chevron_type)
		{
			while (arg[i] == chevron_type)
				i++;
		}
		i++;
	}
	return (input_len_dif);
}

static int	chevron_found_inside(char *arg)
{
	int	input_len_dif;

	input_len_dif = 0;
	input_len_dif = count_chevrons_by_type(arg, input_len_dif, '>');
	input_len_dif = count_chevrons_by_type(arg, input_len_dif, '<');
	return (input_len_dif);
}

static void	handle_chevron_symbol(char *input,
		char *updated_input, int *i, int *j)
{
	char	chevron_type;

	if (input[*i] == '<' || input[*i] == '>')
	{	
		chevron_type = input[*i];
		updated_input[*j] = ' ';
		*j += 1;
		while (input[*i] == chevron_type)
		{
			updated_input[*j] = chevron_type;
			*j += 1;
			*i += 1;
		}
		updated_input[*j] = ' ';
	}
	else
	{	
		updated_input[*j] = input[*i];
		*i += 1;
	}
	*j += 1;
}

static char	*separate_chevrons(char *input, int input_len_dif)
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
		handle_chevron_symbol(input, updated_input, &i, &j);
	}
	updated_input[j] = '\0';
	return (updated_input);
}

char	*isolate_chevrons_symbols(char *input)
{
	int		input_len_dif;
	char	*updated_input;

	input_len_dif = chevron_found_inside(input);
	if (input_len_dif != 0)
		updated_input = separate_chevrons(input, input_len_dif);
	else
		updated_input = ft_strdup(input);
	free(input);
	return (updated_input);
}
