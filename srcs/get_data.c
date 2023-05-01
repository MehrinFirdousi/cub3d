/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 08:56:25 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/01 12:57:02 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_map **data)
{
	*data = (t_map *) malloc(sizeof (t_map));
	(*data)->path_north = NULL;
	(*data)->path_south = NULL;
	(*data)->path_west = NULL;
	(*data)->path_east = NULL;
}

void get_player(t_map *map, t_pos *pos)
{
	int y;
	int x;
	
	y = 0;
	while(map->map[y])
	{
		x = 0;
		while(map->map[y][x])
		{
			if(map->map[y][x] == 'N' || map->map[y][x] == 'W'
				|| map->map[y][x] == 'S' || map->map[y][x] == 'E')
			{
				if(map->map[y][x] == 'N')
					pos->pa = deg_to_rad(90);
				if(map->map[y][x] == 'W')
					pos->pa = deg_to_rad(180);
				if(map->map[y][x] == 'S')
					pos->pa = deg_to_rad(270);
				if(map->map[y][x] == 'E')
					pos->pa = deg_to_rad(0);
				pos->px = x;
				pos->py = y;
			}
			x++;
		}	
		y++;
	}
}

t_map	*get_data(char *line, t_pos *pos)
{
	t_map	*data;
	int i;
	
	data = NULL;
	init_data(&data);
	i = convert_texture(line, data, 0);
	i += convert_texture(&line[i], data, 1);
	get_map(&line[i], data, pos);
	get_player(data, pos);
	return (data);
}
