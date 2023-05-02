/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:37:50 by mfirdous          #+#    #+#             */
/*   Updated: 2023/04/27 12:37:51 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*empty_string(void)
{
	char	*s;

	s = (char *)malloc(1 * sizeof(char));
	if (!s)
		return (NULL);
	s[0] = '\0';
	return (s);
}

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*ss;

	if (!s || !f || ft_strlen(s) == 0)
		return (empty_string());
	ss = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!ss)
		return (NULL);
	i = 0;
	while (s[i] != 0)
	{
		ss[i] = f(i, s[i]);
		i++;
	}
	ss[i] = 0;
	return ((char *)ss);
}
