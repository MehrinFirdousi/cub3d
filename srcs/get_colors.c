/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:25:04 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/04 01:09:57 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_subline(const char *line)
{
	int		i;

	while (*line == ' ')
		++line;
	if (*line == '\0')
		put_error("No colors");
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

static void validate_surface(int *colors, char *line, t_map *map)
{
	int surface;

	if (colors[0] < 0 || colors[0] > 255 || colors[1] < 0
		|| colors[1] > 255 || colors[2] < 0 || colors[2] > 255)
		put_error("color range 0 -> 255");
	surface = check_surface(line);
	if (surface == E_FLOOR)
		map->floor_color = create_trgb(0, colors[0], colors[1], colors[2]);
	else if(surface == E_CEIL)
		map->ceil_color = create_trgb(0, colors[0], colors[1], colors[2]);

}

static void check_duplicate_sides(char *line)
{
	int i;
	char c;

	i = 0;
	while(line[i] && line[i] == ' ')
		i++;
	c = line[i];
	while(line[i] && line[i] != '\n')
		i++;
	i++;
	while(line[i] && line[i] == '\n')
		i++;
	while(line[i] && line[i] == ' ')
		i++;
	if(line[i] == c)
		put_error("Duplicate Sides");	
}

void	get_colors(char *line, t_map *map)
{
	int		i;
	char	*str;
	int		*colors;

	check_duplicate_sides(line);
	i = 0;
	colors = malloc(sizeof(int) * 3);
	while(line[i] && line[i] == ' ')
		i++;
	str = get_subline(&line[i + 2]);
	colors[0] = valid_color(str);
	i = cur_index(str, ',');
	if (!str[i])
		put_error("Not valid colors!!");
	colors[1] = valid_color(&str[i + 1]);
	i += cur_index(&str[i + 1], ',') + 1;
	if (!str[i])
		put_error("Not valid colors!!");
	colors[2] = valid_color(&str[i + 1]);
	i += cur_index(&str[i + 1], ',') + 1;
	if (str[i] == ' ' || str[i] == ',')
		put_error("Must be value of 3 color");
	printf("%d %d %d\n", colors[0], colors[1], colors[2]);	
	validate_surface(colors, line, map);
	free(str);
}

