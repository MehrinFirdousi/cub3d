/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:10:18 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/16 23:18:31 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	mapx_len(const char *line, t_map *map)
{
	int	i;
	int	n;
	int	max;
	int	cnt;

	i = 0;
	n = 0;
	max = 0;
	cnt = 0;
	while (line[i] != '\0')
	{
		while (line[i] && line[i] != '\n')
		{
			if (!defined_symbol(line[i]))
				put_error("Undefined Symbol", map);
			i++;
		}
		cnt++;
		if (i - n > max)
			max = i - n;
		if (line[i])
			n = i++;
	}
	return (max - 1);
}

static int	mapy_len(const char *line, t_map *map)
{
	int	i;
	int	cnt;
	int	len;

	i = 0;
	cnt = 1;
	(void)map;
	len = ft_strlen(line) - 1;
	while (line[len] && ft_is_space(line[len]))
		len--;
	while (line[i] && ft_is_space(line[i]))
		i++;
	while (i < len)
	{
		if (line[i] == '\n')
			cnt++;
		i++;
	}
	return (cnt);
}

void	fill_map(t_map *map)
{
	int	y;
	int	x;

	y = 0;
	map->player_cnt = 0;
	while (y < map->map_height)
	{
		x = 0;
		while (x < map->map_width)
		{
			if (map->map[y][x] == ' ')
				map->map[y][x] = '1';
			x++;
		}
		y++;
	}
}

static void	check_mini_map(char *line, t_map *map)
{
	map->map_width = mapx_len(line, map);
	map->map_height = mapy_len(line, map);
	if (map->map_height < 3 || map->map_width < 3)
	{
		free_paths(map);
		ft_printf("ERROR\nInvalid map\n");
		exit(1);
	}
}

void	get_map(char *line, t_map *map)
{
	int	i;
	int	y;

	check_mini_map(line, map);
	map->map = ft_malloc(sizeof(char *) * (map->map_height + 1));
	y = 0;
	while (*line && *line == '\n')
		line++;
	while (y < map->map_height)
	{
		map->map[y] = ft_malloc(sizeof(char) * (map->map_width + 1));
		i = 0;
		while (*line && *line != '\n')
			map->map[y][i++] = *(line++);
		while (i < map->map_width)
			map->map[y][i++] = ' ';
		map->map[y++][i] = '\0';
		if (*line)
			line++;
	}
	map->map[y] = NULL;
}
