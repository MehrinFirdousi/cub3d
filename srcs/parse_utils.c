/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:25:06 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/14 21:06:33 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_color(const char *str)
{
	int	num;
	int	i;

	i = 0;
	if (!str[i])
		return (-1);
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	num = 0;
	if (!str[i])
		return (-1);
	while (ft_isdigit(str[i]))
	{
		num = num * 10 + (str[i++] - '0');
		if (num > MAX_COLOR)
			return (-1);
	}
	while (str[i] == ' ' || str[i] == '\t')
		++str;
	if (str[i] != '\0' && str[i] != ',' && str[i] != '\n')
		return (-1);
	return (num);
}

int	cur_index(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		++i;
	return (i);
}

void	free_paths(t_map *map)
{
	if (map->n_texture.path)
		free(map->n_texture.path);
	if (map->s_texture.path)
		free(map->s_texture.path);
	if (map->w_texture.path)
		free(map->w_texture.path);
	if (map->e_texture.path)
		free(map->e_texture.path);
	if (map->file)
		free(map->file);
}

void	free_malloced(t_map *map)
{
	int	i;

	free_paths(map);
	i = 0;
	while (i < FRAME_TOTAL)
	{
		if (map->torch[i].path)
			free(map->torch[i].path);
		i++;
	}
	if (map->c_door_texture.path)
		free(map->c_door_texture.path);
	i = 0;
	while (i < map->map_height)
		free(map->map[i++]);
	if (map->map_height)
		free(map->map);
}

int	check_surface(const char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (ft_strncmp(&line[i], "F ", 2) == 0)
		return (E_FLOOR);
	else if (ft_strncmp(&line[i], "C ", 2) == 0)
		return (E_CEIL);
	return (-1);
}
