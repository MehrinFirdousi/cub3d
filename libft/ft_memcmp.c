/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:32:26 by mfirdous          #+#    #+#             */
/*   Updated: 2023/04/27 12:32:27 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_byte;
	unsigned char	*s2_byte;
	size_t			i;

	s1_byte = (unsigned char *)s1;
	s2_byte = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1_byte[i] != s2_byte[i])
		{
			if (s1_byte + i != NULL && s2_byte + i != NULL)
				return (s1_byte[i] - s2_byte[i]);
			else if (s1_byte + i)
				return (s1_byte[i]);
			else if (s2_byte + i)
				return (s2_byte[i]);
		}
		i++;
	}
	return (0);
}
