/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:38:35 by mfirdous          #+#    #+#             */
/*   Updated: 2023/04/27 12:38:36 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*empty_string(void)
{
	char	*s;

	s = ft_malloc(1);
	if (!s)
		return (NULL);
	s[0] = '\0';
	return (s);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*s2;
	size_t	strlen;
	size_t	char_count;

	if (!s || (size_t)start >= ft_strlen((char *)s)
		|| ft_strlen((char *)s) == 0)
		return (empty_string());
	strlen = ft_strlen((char *)s);
	char_count = 0;
	if (len + start < strlen)
		char_count = (len);
	else
		char_count = (strlen - (size_t)start);
	s2 = ft_malloc(char_count + 1);
	if (!s2)
		return (NULL);
	i = 0;
	while (i < char_count)
	{
		s2[i] = s[i + (size_t)start];
		i++;
	}
	s2[i] = '\0';
	return (s2);
}
