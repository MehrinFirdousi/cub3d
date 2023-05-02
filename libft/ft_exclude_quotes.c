/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exclude_quotes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 12:30:15 by mfirdous          #+#    #+#             */
/*   Updated: 2023/04/27 12:30:16 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_without_quotes(char *s)
{
	int			i;
	int			count;
	t_inside	inside;

	count = 0;
	i = -1;
	ft_bzero(&inside, sizeof(inside));
	while (s[++i])
	{
		if (s[i] == '\'' && !inside.dquotes)
			inside.quotes = !inside.quotes;
		else if (s[i] == '\"' && !inside.quotes)
			inside.dquotes = !inside.dquotes;
		else
			count++;
	}
	return (count);
}

char	*ft_exclude_quotes(char *str)
{
	int			i;
	int			reach;
	char		*nstr;
	t_inside	inside;

	i = -1;
	reach = 0;
	ft_bzero(&inside, sizeof(inside));
	nstr = ft_malloc(count_without_quotes(str) + 1);
	while (str[++i])
	{
		if (str[i] == '\'' && !inside.dquotes)
			inside.quotes = !inside.quotes;
		else if (str[i] == '\"' && !inside.quotes)
			inside.dquotes = !inside.dquotes;
		else
			nstr[reach++] = str[i];
	}
	nstr[reach] = 0;
	return (nstr);
}
