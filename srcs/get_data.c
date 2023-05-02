/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 08:56:25 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/01 23:07:04 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_map *data)
{
	data->path_north = NULL;
	data->path_south = NULL;
	data->path_west = NULL;
	data->path_east = NULL;
}

static void set_player_pos(t_map *map, t_player *pos, int x, int y)
{
	pos->px = x;
	map->player_x = x;
	pos->py = y;
	map->player_y = y;
}

static void get_player(t_map *map, t_player *pos)
{
	int y;
	int x;
	
	y = -1;
	while(map->map[++y])
	{
		x = -1;
		while(map->map[y][++x])
		{
			if(player_symbol(map->map[y][x]))
			{
				if(map->map[y][x] == 'N')
					pos->pa = deg_to_rad(270);
				if(map->map[y][x] == 'W')
					pos->pa = deg_to_rad(180);
				if(map->map[y][x] == 'S')
					pos->pa = deg_to_rad(90);
				if(map->map[y][x] == 'E')
					pos->pa = deg_to_rad(0);
				map->map[y][x] = 'P';
				set_player_pos(map, pos, x, y);
			}
		}	
	}
}

t_map	*get_data(char *line, t_map *data, t_player *pos)
{
	int i;
	
	init_data(data);
	i = get_upper_map(line, data, 0);
	i += get_upper_map(&line[i], data, 1);
	get_map(&line[i], data);
	get_player(data, pos);
	return (data);
}
