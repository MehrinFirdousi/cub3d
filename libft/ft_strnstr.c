/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:38:16 by mfirdous          #+#    #+#             */
/*   Updated: 2023/04/27 12:38:17 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	if (ft_strlen((char *)needle) == 0)
		return ((char *)haystack);
	i = 0;
	while (i < len && haystack[i] != 0)
	{
		j = 0;
		while (needle[j] != 0 && haystack[i + j] == needle[j] && i + j < len)
			if (needle[++j] == 0)
				return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
