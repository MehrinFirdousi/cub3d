/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:25:06 by ahassan           #+#    #+#             */
/*   Updated: 2023/04/29 23:03:31 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_color(const char *str)
{
	int	num;
	int i;
	
	i = 0;
	while (ft_is_space(str[i]))
		i++;
	if (!ft_isdigit(str[i]))
		return (-1);
	num = 0;
	while (ft_isdigit(str[i]))
		num = num * 10 + (str[i++] - '0');
	while (str[i] == ' ')
		++str;
	if (str[i] != '\0' && str[i] != ',' && str[i] != '\n')
		put_error("Not valid colors");
	return (num);
}

int	cur_index(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		++i;
	return (i);
}

void	put_error(const char *error)
{
	write(2, "ERROR\n", ft_strlen("ERROR\n"));
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	exit(1);
}

int	check_surface(const char *line)
{
	if (ft_strncmp(line, "F ", 2) == 0)
		return (0);
	if (ft_strncmp(line, "C ", 1) == 0)
		return (1);
	put_error("Not valid color side");
	return (0);
}