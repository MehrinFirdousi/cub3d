/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:57:22 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/16 23:17:26 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_extra_texture(char *line)
{
	if (ft_strncmp(line, "DO ", 3) == 0 || ft_strncmp(line, "T1 ", 3) == 0
		|| ft_strncmp(line, "T2 ", 3) == 0 || ft_strncmp(line, "T3 ", 3) == 0
		|| ft_strncmp(line, "T4 ", 3) == 0 || ft_strncmp(line, "T5 ", 3) == 0
		|| ft_strncmp(line, "T6 ", 3) == 0 || ft_strncmp(line, "DC ", 3) == 0)
		return (true);
	return (false);
}

void	put_error(const char *error, t_map *map)
{
	write(2, "ERROR\n", ft_strlen("ERROR\n"));
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	free_malloced(map);
	exit(1);
}

int	reset_line(char *line, int i)
{
	int	j;

	j = i--;
	while (line[j] != '\n')
		j--;
	return (i - j);
}

bool	is_door_texture(int *flag, char *path, t_map *data)
{
	if (*flag == (FRAME_TOTAL + 1) && !data->c_door_texture.path)
	{
		data->c_door_texture.path = path;
		return (true);
	}
	if (*flag == (FRAME_TOTAL + 2) && !data->o_door_texture.path)
	{
		data->o_door_texture.path = path;
		return (true);
	}
	return (false);
}
