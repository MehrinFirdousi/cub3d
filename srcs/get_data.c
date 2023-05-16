/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 08:56:25 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/16 23:08:34 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_map *map)
{
	int	i;

	map->map_height = 0;
	map->map_width = 0;
	map->player_cnt = 0;
	map->floor_color = -1;
	map->ceil_color = -1;
	map->c_door_texture.path = NULL;
	map->o_door_texture.path = NULL;
	i = (int)FRAME_TOTAL;
	while (--i > -1)
		map->torch[i].path = NULL;
	map->n_texture.path = NULL;
	map->s_texture.path = NULL;
	map->w_texture.path = NULL;
	map->e_texture.path = NULL;
	map->file = NULL;
}

static void	set_player_pos(t_map *map, t_player *p, int x, int y)
{
	p->px = x;
	map->player_x = x;
	p->py = y;
	map->player_y = y;
	p->py = y;
	map->player_y = y;
}

static double	deg_to_rad(double x)
{
	return (x * M_PI / 180.0);
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
	int	i;

	i = get_upper_map(line, data);
	i += bonus_parse(&line[i], data);
	i -= reset_line(line, i);
	get_map(&line[i], data);
	check_valid_map(data);
	check_empty_line(data);
	valid_player(data);
	fill_map(data);
	get_player(data, p);
}
