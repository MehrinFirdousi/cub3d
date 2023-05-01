/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/30 17:10:18 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/01 22:50:18 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int defined_symbole(char c)
{
	if (c == '0' || c == '1' || c == ' ' || c == 'N' 
			|| c == 'E' || c == 'S' || c == 'W')
				return 1;
	return 0;			
}

static void valid_player(t_map *map)
{
	if(map->player_cnt > 1)
		put_error("Multiplayer!");
	if(map->player_cnt == 0)
		put_error("No Player!");			
}

static void is_closed(char **map, int y, int x)
{
	if (y == 0 || map[y - 1][x] == ' ')
		put_error("Map must be closed");
	if (!map[y + 1] || map[y + 1][x] == ' ')
		put_error("Map must be closed");
	if (x == 0 || map[y][x - 1] == ' ')
		put_error("Map must be closed");
	if (map[y][x + 1] == ' ' || !map[y][x + 1])
		put_error("Map must be closed");
}

static void check_valid_map(t_map *map)
{
	int y;
	int x;

	y = -1;
	map->player_cnt = 0;
	while (++y < map->map_height)
	{
		x = -1;
		while (++x < map->map_width)
		{
			if (defined_symbole(map->map[y][x]))
			{
				if(map->map[y][x] == 'N' || map->map[y][x] == 'E' 
					|| map->map[y][x] == 'S'|| map->map[y][x] == 'W')
						map->player_cnt++;
				if(map->map[y][x] == '0')
					is_closed(map->map, y, x);
			}
			else
				put_error("Undefined Symbole");
		}
	}
	valid_player(map);
}

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
			x++;
		}
		y++;
	}		
}

void	get_map(char *line, t_map *map)
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