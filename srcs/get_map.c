/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:10:18 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/02 17:15:10 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	mapx_len(const char *line)
{
	int	i;
	int	n;
	int	max;
	int cnt;

	i = 0;
	n = 0;
	max = 0;
	cnt = 0;
	// int len =(int)ft_strlen(line);
	while (line[i] != '\0')
	{
		while (line[i] && line[i] != '\n')
			i++;
		cnt++;
		// if(i >= len - 1) //stop i if exceeds null 
		// 	return max;
		if (i - n > max)
			max = i - n;
		if(line[i])
			n = i++;
	}
	// printf("cnnnt %d\n", cnt);
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
	return (cnt + 1);
}

void fill_map(t_map *map)
{
	int y;
	int x;

	y = 0;
	map->player_cnt = 0;
	while (y < map->map_height)
	{
		x = 0;
		while (x < map->map_width)
		{
			if (map->map[y][x] == ' ')
				map->map[y][x] = '1';
			if (player_symbol(map->map[y][x]))
				map->map[y][x] = 'P';
			x++;
		}
		y++;
	}		
}

void	get_map(char *line, t_map *map)
{
	int		i;
	int		y;

	map->map_width = mapx_len(line);
	map->map_height = mapy_len(line);
	if(map->map_height < 3 || map->map_height < 3)
		put_error("Invalid map");
	map->map = malloc(sizeof (char *) * (map->map_height + 1));

	y = 0;
	while (y < map->map_height)
	{
		map->map[y] = (char *) malloc(sizeof (char) * (map->map_width + 1));
		i = 0;
		while (*line && *line != '\n')
			map->map[y][i++] = *(line++);
		while (i < map->map_width)
			map->map[y][i++] = ' ';
		map->map[y++][i] = '\0';
		line++;
	}
	map->map[y] = NULL;
	check_valid_map(map);
	fill_map(map);
}