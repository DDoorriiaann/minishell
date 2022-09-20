/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_char.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybaudoui <ybaudoui@student.42angouleme.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 16:11:24 by ybaudoui          #+#    #+#             */
/*   Updated: 2022/09/01 10:36:50 by ybaudoui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_char(char const *s1, char const *s2, char *separator)
{
	size_t	i;
	char	*str;

	if ((s1 == 0) || (s2 == 0))
		return (NULL);
	i = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(separator);
	str = malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, i + 1);
	ft_strlcpy(str + ft_strlen(s1), separator, i + 1);
	ft_strlcpy(str + ft_strlen(s1) + ft_strlen(separator), s2, i + 1);
	return (str);
}
