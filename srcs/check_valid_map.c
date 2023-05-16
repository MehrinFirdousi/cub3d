/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 23:11:38 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/16 23:19:02 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	valid_player(t_map *map)
{
	if (map->player_cnt > 1)
		put_error("Multiplayer!", map);
	if (map->player_cnt == 0)
		put_error("No Player!", map);
}

static void	is_closed(t_map *m, int y, int x)
{
	if (y == 0 || m->map[y - 1][x] == ' ')
		put_error("Map must be closed", m);
	if (!m->map[y + 1] || m->map[y + 1][x] == ' ')
		put_error("Map must be closed", m);
	if (x == 0 || m->map[y][x - 1] == ' ')
		put_error("Map must be closed", m);
	if (m->map[y][x + 1] == ' ' || !m->map[y][x + 1])
		put_error("Map must be closed", m);
}

static bool	is_walled(t_map *m, int y, int x)
{
	if (y == 0 || !m->map[y + 1] || !m->map[y][x + 1])
		put_error("Doors must be walled", m);
	if (m->map[y][x + 1] == '1' && m->map[y][x - 1] == '1' &&
		m->map[y + 1][x] == '1' && m->map[y - 1][x] == '1')
		return (false);
	if (m->map[y][x + 1] == '1')
		if (m->map[y][x - 1] == '1')
			return (true);
	if (m->map[y + 1][x] == '1')
		if (m->map[y - 1][x] == '1')
			return (true);
	return (false);
}

void	check_empty_line(t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while (++y < map->map_height)
	{
		x = 0;
		while (map->map[y][x] == ' ' || map->map[y][x] == '\t')
			x++;
		if (!map->map[y][x])
			put_error("Empty Line", map);
	}
}

void	check_valid_map(t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while (++y < map->map_height)
	{
		x = -1;
		while (++x < map->map_width)
		{
			if (defined_symbol(map->map[y][x]))
			{
				if (player_symbol(map->map[y][x]))
					map->player_cnt++;
				if (map->map[y][x] == '0' || player_symbol(map->map[y][x]))
					is_closed(map, y, x);
				if (map->map[y][x] == 'D')
					if (!is_walled(map, y, x))
						put_error("Must be walled", map);
			}
		}
	}
}
