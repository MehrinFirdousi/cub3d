/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 18:57:22 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/14 21:08:34 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_extra_texture(char *line)
{
	if (ft_strncmp(line, "DO ", 3) == 0 || ft_strncmp(line, "T1 ", 3) == 0
		|| ft_strncmp(line, "T2 ", 3) == 0 || ft_strncmp(line, "T3 ", 3) == 0
		|| ft_strncmp(line, "T4 ", 3) == 0 || ft_strncmp(line, "T5 ", 3) == 0
		|| ft_strncmp(line, "T6 ", 3) == 0 || ft_strncmp(line, "DC ", 3) == 0)
		return (1);
	return (0);
}

void	put_error(const char *error, t_map *map)
{
	write(2, "ERROR\n", ft_strlen("ERROR\n"));
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	free_malloced(map);
	exit(1);
}

bool	is_door_texture(int *flag, char *path, t_map *data)
{
	if (*flag == (FRAME_TOTAL + 1) && !data->c_door_texture.path)
	{
		data->c_door_texture.path = path;
		return (true);
	}
	if (*flag == (FRAME_TOTAL + 2) && !data->o_door_texture.path)
	{
		data->o_door_texture.path = path;
		return (true);
	}
	return (false);
}

void	print_map(t_map *map, t_player *p)
{
	int	i;

	i = 0;
	printf("height == %d\n", map->map_height);
	printf("width == %d\n", map->map_width);
	printf("py == %lf\n", p->py);
	printf("px == %lf\n", p->px);
	printf("pa == %lf\n", p->pa);
	printf("{%s}\n", map->n_texture.path);
	printf("{%s}\n", map->s_texture.path);
	printf("{%s}\n", map->w_texture.path);
	printf("{%s}\n", map->e_texture.path);
	printf("Door {%s}\n", map->c_door_texture.path);
	printf("Door c {%s}\n", map->o_door_texture.path);
	i = -1;
	while (++i < FRAME_TOTAL)
		printf("T%i {%s}\n", i + 1, map->torch[i].path);
	i = 0;
	while (map->map[i])
		ft_printf("{%s}\n", map->map[i++]);
}
