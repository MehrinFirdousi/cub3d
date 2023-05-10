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
	data->map_height = 0;
	data->map_width = 0;
	data->player_cnt = 0;
	data->floor_color = -1;
	data->ceil_color = -1;
	data->q_flag = 0;
	data->c_door_texture.path = NULL;
	data->torch[0].path = NULL;
	data->torch[1].path = NULL;
	data->torch[2].path = NULL;
	data->torch[3].path = NULL;
	data->torch[4].path = NULL;
	data->torch[5].path = NULL;
	data->n_texture.path = NULL;
	data->s_texture.path = NULL;
	data->w_texture.path = NULL;
	data->e_texture.path = NULL;
	data->file = NULL;
}

static void set_player_pos(t_map *map, t_player *p, int x, int y)
{
	p->px = x;
	map->player_x = x;
	p->py = y;
	map->player_y = y;
	p->py = y;
	map->player_y = y;
}

static void	get_player(t_map *map, t_player *p)
{
	int	y;
	int	x;

	y = -1;
	while (map->map[++y])
	{
		x = -1;
		while (map->map[y][++x])
		{
			if (player_symbol(map->map[y][x]))
			{
				if (map->map[y][x] == 'N')
					p->pa = deg_to_rad(270);
				if (map->map[y][x] == 'W')
					p->pa = deg_to_rad(180);
				if (map->map[y][x] == 'S')
					p->pa = deg_to_rad(90);
				if (map->map[y][x] == 'E')
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
	if(is_texture(&line[i]) || is_color(&line[i]))
		put_error("Duplicate data sides", data);
	i += valid_extra_textures(&line[i], data);
	while (line[--i] != '\n');
	get_map(&line[i], data);
	get_player(data, p);
}
