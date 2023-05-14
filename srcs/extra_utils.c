/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:57:22 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/14 20:34:33 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_extra_texture(char *line)
{
	if (ft_strncmp(line, "DO ", 3) == 0 || ft_strncmp(line, "T1 ", 3) == 0
		|| ft_strncmp(line, "T2 ", 3) == 0 || ft_strncmp(line, "T3 ", 3) == 0
		|| ft_strncmp(line, "T4 ", 3) == 0 || ft_strncmp(line, "T5 ", 3) == 0
		|| ft_strncmp(line, "T6 ", 3) == 0 || ft_strncmp(line, "DC ", 3) == 0) 
		return (1);
	return (0);
}

void	put_error(const char *error, t_map *map)
{
	write(2, "ERROR\n", ft_strlen("ERROR\n"));
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	free_malloced(map);
	exit(1);
}
