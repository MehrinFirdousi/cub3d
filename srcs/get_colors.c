/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:25:04 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/10 23:51:43 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void free_colors_utils(char *str, int *colors, t_map *map, int i)
{
	if (!str[i])
	{
		free(str);
		free(colors);
		put_error("Not valid colors!!", map);
	}
}

static void is_valid_range(char *str, int *colors, t_map *map)
{
	if (colors[0] < 0 || colors[0] > 255 || colors[1] < 0
		|| colors[1] > 255 || colors[2] < 0 || colors[2] > 255)
		{
			free(colors);
			free(str);
			put_error("color range 0 -> 255", map);
		}
}

static char	*get_subline(const char *line, t_map *map)
{
	int		i;

	while (*line == ' ')
		++line;
	if (*line == '\0')
		put_error("No colors", map);
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		if(line[i])
			++i;
	return (ft_substr(line, 0, i));
}

static int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

static void validate_surface(int *colors, char *line, char *str, t_map *map)
{
	int surface;

	is_valid_range(str, colors, map);
	surface = check_surface(line, map);
	if (surface == E_FLOOR)
	{
		if(map->floor_color > -1)
		{
			free(str);
			free(colors);
			put_error("Duplicate colors sides", map);
		}
		map->floor_color = create_trgb(0, colors[0], colors[1], colors[2]);
		free(colors);
	}
	else if(surface == E_CEIL)
	{
		if(map->ceil_color > -1)
		{
			free(str);
			free(colors);
			put_error("Duplicate colors sides", map);	
		}
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
	colors = malloc(sizeof(int) * 3);
	while(line[i] && line[i] == ' ')
		i++;
	str = get_subline(&line[i + 2], map);
	colors[0] = valid_color(str);
	i = cur_index(str, ',');
	free_colors_utils(str, colors, map, i);
	colors[1] = valid_color(&str[i + 1]);
	i += cur_index(&str[i + 1], ',') + 1;
	free_colors_utils(str, colors, map, i);
	colors[2] = valid_color(&str[i + 1]);
	i += cur_index(&str[i + 1], ',') + 1;
	if (str[i] != '\0')
	{
		free(str);
		free(colors);
		put_error("Must be 3 color", map);
	}
	printf("%d %d %d\n", colors[0], colors[1], colors[2]);	
	validate_surface(colors, line, str, map);
	free(str);
}
