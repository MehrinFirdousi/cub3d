/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:10:18 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/01 20:26:19 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	mapx_len(const char *line)
{
	int	i;
	int	n;
	int	max;

	i = 0;
	n = 0;
	max = 0;
	while (line[i] != '\0')
	{
		while (line[i] != '\0' && line[i] != '\n')
			++i;
		if (i - n > max)
			max = i - n;
		n = i++;
	}
	return (max);
}

static int	mapy_len(const char *line)
{
	int	i;
	int	cnt;

	i = -1;
	cnt = 0;
	while (line[++i])
		if (line[i] == '\n')
			cnt++;
	return (cnt);
}

void	get_map(char *line, t_map *map, t_pos *pos)
{
	int		i;
	int		y;
	char	*str;
	
	(void)str;
	(void)pos;
	map->map_width = mapx_len(line);
	map->map_height = mapy_len(line);
	map->map = malloc(sizeof (char *) * (map->map_height + 1));

	y = 0;
	while (y < map->map_height)
	{
		map->map[y] = (char *) malloc(sizeof (char) * (map->map_width + 1));
		i = 0;
		while (*line && *line != '\n')
		{
			if(*line == ' ')
				map->map[y][i++] = '1', line++;
			else	
				map->map[y][i++] = *(line++);
		}
		while (i < map->map_width)
			map->map[y][i++] = '1';
		map->map[y++][i] = '\0';
		line++;
	}
	map->map[y] = NULL;
}