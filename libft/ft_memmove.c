/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:32:37 by mfirdous          #+#    #+#             */
/*   Updated: 2023/04/27 12:32:38 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	unsigned char		*s;
	size_t				i;

	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	i = 0;
	while (d > s && i < n)
		i++;
	while (i > 0)
	{
		d[i - 1] = s[i - 1];
		i--;
	}
	while (d < s && i < n)
	{
		if (d[i] != s[i])
			d[i] = s[i];
		i++;
	}
	return ((void *)d);
}
