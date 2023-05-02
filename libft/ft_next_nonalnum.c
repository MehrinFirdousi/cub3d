/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_next_nonalnum.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:32:47 by mfirdous          #+#    #+#             */
/*   Updated: 2023/04/27 12:32:48 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_next_nonalnum(char *str, int start)
{
	int	i;

	i = start;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	return (i);
}
