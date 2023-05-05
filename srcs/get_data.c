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

static void set_player_pos(t_map *map, t_player *p, int x, int y)
{
	p->px = x;
	map->player_x = x;
	p->py = y;
	map->player_y = y;
	p->py = y;
	map->player_y = y;
}

static void get_player(t_map *map, t_player *p)
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
					p->pa = deg_to_rad(270);
				if(map->map[y][x] == 'W')
					p->pa = deg_to_rad(180);
				if(map->map[y][x] == 'S')
					p->pa = deg_to_rad(90);
				if(map->map[y][x] == 'E')
					p->pa = deg_to_rad(0);
				map->map[y][x] = 'P';
				set_player_pos(map, p, x, y);
			}
		}	
	}
}

void	get_data(char *line, t_map *data, t_player *p)
{
	int i;
	
	i = get_upper_map(line, data);
	if(is_texture(&line[i]))
		put_error("duplicate_sides", data);
	while (line[--i] != '\n');
	get_map(&line[i], data);
	get_player(data, p);
}
