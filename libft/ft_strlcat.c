/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:37:34 by mfirdous          #+#    #+#             */
/*   Updated: 2023/04/27 12:37:35 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	y;
	size_t	dst_len;
	size_t	src_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen((char *)src);
	if (dst_len >= dstsize)
		return (dstsize + src_len);
	i = 0;
	while (dst[i] != 0)
		i++;
	y = 0;
	while (i + 1 < dstsize && src[y] != 0)
		dst[i++] = src[y++];
	if (i < dstsize)
		dst[i] = 0;
	while (src[y++] != 0)
		i++;
	return (i);
}
