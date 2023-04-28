/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:25:04 by ahassan           #+#    #+#             */
/*   Updated: 2023/04/28 19:52:12 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	valid_range(int *colors)
{
	if (colors[0] < 0 || colors[0] > 255 || colors[1] < 0
		|| colors[1] > 255 || colors[2] < 0 || colors[2] > 255)
		put_error("colo range 0 -> 255");
}

static char	*get_subline(const char *line)
{
	int		i;

	while (*line == ' ')
		++line;
	if (*line == '\0')
		put_error("No colors");
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		++i;
	return (ft_substr(line, 0, i));
}

static void	get_colors(char *line, t_map *map)
{
	int		i;
	char	*str;
	int *colors;
	int surface;

	colors = malloc(sizeof(int) * 3);
	
	str = get_subline(&line[2]);
	colors[0] = valid_color(str);
	i = cur_index(str, ',');
	colors[1] = valid_color(&str[i + 1]);
	i += cur_index(&str[i + 1], ',') + 1;
	colors[2] = valid_color(&str[i + 1]);
	i += cur_index(&str[i + 1], ',') + 1;
	if (str[i] != '\0')
		put_error("Must be value of 3 color");
	valid_range(colors);
	surface = check_surface(line);
	if(surface == 0)
		map->floor_color = colors;
	else if(surface == 1)
		map->ceil_color = colors;
	free(str);
}

int	convert_color(char *line, t_map *map)
{
	int		i;
	int		color_count;

	i = 0;
	color_count = 0;
	while (line[i] != '\0')
	{
		while (line[i] == '\n')
			++i;
		if (color_count == 2)
			return (i);
		get_colors(&line[i], map);
		++color_count;
		i += cur_index(&line[i], '\n');
	}
	if (line[i] == '\0')
		put_error("Map is missing one or more data");
	return (i);
}
