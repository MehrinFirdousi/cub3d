/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:37:18 by mfirdous          #+#    #+#             */
/*   Updated: 2023/04/27 12:37:19 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strfjoin(char *buf, char *new_block)
{
	char	*new_buf;
	int		i;
	int		len1;
	int		len2;

	len1 = ft_strlen(buf);
	len2 = ft_strlen(new_block);
	new_buf = (char *)ft_malloc((len1 + len2 + 1) * sizeof(char));
	if (!new_buf)
		return (0);
	i = -1;
	while (++i < len1)
		new_buf[i] = (buf)[i];
	while (i < len1 + len2)
	{
		new_buf[i] = (new_block)[i - len1];
		i++;
	}
	new_buf[i] = 0;
	free(buf);
	free(new_block);
	return (new_buf);
}
