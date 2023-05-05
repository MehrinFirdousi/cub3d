/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:25:04 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/05 23:40:30 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

	if (colors[0] < 0 || colors[0] > 255 || colors[1] < 0
		|| colors[1] > 255 || colors[2] < 0 || colors[2] > 255)
		free(colors), free(str), put_error("color range 0 -> 255", map);
	surface = check_surface(line, map);
	if (surface == E_FLOOR)
		map->floor_color = create_trgb(0, colors[0], colors[1], colors[2]), free(colors);
	else if(surface == E_CEIL)
		map->ceil_color = create_trgb(0, colors[0], colors[1], colors[2]), free(colors);

}

static void check_duplicate_sides(char *line, t_map *map)
{
	int i;
	char c;

	i = 0;
	while(line[i] && line[i] == ' ')
		i++;
	c = line[i];
	while(line[++i])
		if(line[i] == c)
			put_error("Duplicate Sides", map);
}

void	get_colors(char *line, t_map *map)
{
	int		i;
	char	*str;
	int		*colors;

	i = 0;
	check_duplicate_sides(line, map);
	colors = malloc(sizeof(int) * 3);
	while(line[i] && line[i] == ' ')
		i++;
	str = get_subline(&line[i + 2], map);
	colors[0] = valid_color(str);
	i = cur_index(str, ',');
	if (!str[i])
		free(str), free(colors), put_error("Not valid colors!!", map);
	colors[1] = valid_color(&str[i + 1]);
	i += cur_index(&str[i + 1], ',') + 1;
	if (!str[i])
		free(str), free(colors), put_error("Not valid colors!!", map);
	colors[2] = valid_color(&str[i + 1]);
	i += cur_index(&str[i + 1], ',') + 1;
	if (str[i] != '\0')
		free(str), free(colors), put_error("Must be 3 color", map);
	printf("%d %d %d\n", colors[0], colors[1], colors[2]);	
	validate_surface(colors, line, str, map);
	free(str);
}

