/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:25:04 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/15 15:20:09 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_colors(char *str, int *colors, t_map *map, char *err_msg)
{
	free(str);
	free(colors);
	put_error(err_msg, map);
}

static char	*get_subline(const char *line)
{
	int	i;

	while (*line == ' ')
		++line;
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		if (line[i])
			++i;
	return (ft_substr(line, 0, i));
}

static int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static void	validate_surface(int *colors, char *line, char *str, t_map *map)
{
	int	surface;

	if (colors[0] < MIN_COLOR || colors[0] > MAX_COLOR
		|| colors[1] < MIN_COLOR || colors[1] > MAX_COLOR
		|| colors[2] < MIN_COLOR || colors[2] > MAX_COLOR)
		free_colors(str, colors, map, "color range 0 -> 255");
	surface = check_surface(line);
	if (surface == E_FLOOR)
	{
		if (map->floor_color > -1)
			free_colors(str, colors, map, "Duplicate colors sides");
		map->floor_color = create_trgb(0, colors[0], colors[1], colors[2]);
		free(colors);
	}
	else if (surface == E_CEIL)
	{
		if (map->ceil_color > -1)
			free_colors(str, colors, map, "Duplicate colors sides");
		map->ceil_color = create_trgb(0, colors[0], colors[1], colors[2]);
		free(colors);
	}
}

void	get_colors(char *line, t_map *map)
{
	int		i;
	char	*str;
	int		*colors;

	i = 0;
	colors = ft_malloc(sizeof(int) * 3);
	while (line[i] && line[i] == ' ')
		i++;
	str = get_subline(&line[i + 2]);
	colors[0] = valid_color(str);
	i = cur_index(str, ',');
	if (!str[i])
		free_colors(str, colors, map, "Must be 3 colors");
	colors[1] = valid_color(&str[i + 1]);
	i += cur_index(&str[i + 1], ',') + 1;
	if (!str[i])
		free_colors(str, colors, map, "Must be 3 colors");
	colors[2] = valid_color(&str[i + 1]);
	i += cur_index(&str[i + 1], ',') + 1;
	if (str[i] != '\0')
		free_colors(str, colors, map, "Must be 3 colors");
	validate_surface(colors, line, str, map);
	free(str);
}
