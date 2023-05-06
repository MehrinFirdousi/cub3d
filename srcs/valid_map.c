/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 23:11:38 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/06 16:56:38 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int player_symbol(char c)
{
	if (c == 'N' || c == 'E' || c == 'S'|| c == 'W')
		return 1;
	return 0;			
}
int defined_symbol(char c)
{
	if (c == '0' || c == '1' || c == ' ' || c == 'N' 
			|| c == 'E' || c == 'S' || c == 'W')
				return 1;
	return 0;			
}

static void valid_player(t_map *map)
{
	if(map->player_cnt > 1)
		put_error("Multiplayer!", map);
	if(map->player_cnt == 0)
		put_error("No Player!", map);			
}

static void is_closed(t_map *m, int y, int x)
{
	if (y == 0 || m->map[y - 1][x] == ' ')
		printf("%d %d-\n", x, y), put_error("Map must be closed", m);
	if (!m->map[y + 1] || m->map[y + 1][x] == ' ')
		printf("%d %d--\n", x, y), put_error("Map must be closed", m);;
	if (x == 0 || m->map[y][x - 1] == ' ')
		printf("%d %d---\n", x, y), put_error("Map must be closed", m);;
	if (m->map[y][x + 1] == ' ' || !m->map[y][x + 1])
		printf("%d %d----\n", x, y), put_error("Map must be closed", m);;
}

void check_valid_map(t_map *map)
{
	int y;
	int x;

	y = -1;
	while (++y < map->map_height)
	{
		x = -1;
		while (++x < map->map_width)
		{
			if (defined_symbol(map->map[y][x]))
			{
				if(player_symbol(map->map[y][x]))
						map->player_cnt++;
				if(map->map[y][x] == '0' || player_symbol(map->map[y][x]))
					is_closed(map, y, x);
			}
			else{
				printf("%d %d\n", y, x);
				put_error("Undefined Symbol", map);
			}
		}
	}
	valid_player(map);
}
