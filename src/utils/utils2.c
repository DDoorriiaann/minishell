/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dguet <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:29:53 by dguet             #+#    #+#             */
/*   Updated: 2022/12/21 14:29:54 by dguet            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	find_word_end(char *input, int index)
{
	while (input[index] && !ft_isspace(input[index]))
	{
		if (ft_is_quote(input[index]))
		{	
			if (find_closing_quote(input, index + 1, input[index]) != ERROR)
				index = find_closing_quote(input, index + 1, input[index]);
		}
		index++;
	}
	return (index);
}

int	go_to_word_end(char *input, int start, int *argc)
{
	int	end;

	end = start;
	if (input[start] && !ft_isspace(input[start]))
	{
		end = find_word_end(input, start);
		if (end != start)
			*argc = *argc + 1;
	}
	return (end);
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
	else
		index = go_to_word_end(input, index, argc);
	return (index);
}
