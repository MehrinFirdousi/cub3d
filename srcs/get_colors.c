/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:25:04 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/02 18:08:49 by ahassan          ###   ########.fr       */
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
	if(surface == E_CEIL)
		map->ceil_color = create_trgb(0, colors[0], colors[1], colors[2]);

}

void	get_colors(char *line, t_map *map)
{
	int		i;
	char	*str;
	int		*colors;
	
	colors = malloc(sizeof(int) * 3);

	str = get_subline(&line[2]);
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
	validate_surface(colors, line, map);
	printf("%d %d %d\n", colors[0], colors[1], colors[2]);
	free(str);
}

