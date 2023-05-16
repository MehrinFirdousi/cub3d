/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_upper_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:29:30 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/16 23:08:48 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_valid_data(int *i, char *line, t_map *data)
{
	while (line[*i] != '\0')
	{
		while (line[*i] && ft_is_space(line[*i]))
			(*i)++;
		if (is_texture(&line[*i]))
		{
			get_textures(&line[*i], data);
			data->texture_cnt++;
		}
		else if (is_color(&line[*i]))
		{
			get_colors(&line[*i], data);
			data->color_cnt++;
		}
		else
			break ;
		*i += cur_index(&line[*i], '\n');
	}
	return (*i);
}

int	get_upper_map(char *line, t_map *data)
{
	int	i;

	i = 0;
	data->texture_cnt = 0;
	data->color_cnt = 0;
	is_valid_data(&i, line, data);
	if (data->color_cnt != 2 || data->texture_cnt != 4)
		put_error("Invalid mandatory data", data);
	if (line[i] == '\0')
		put_error("Map is missing one or more data", data);
	return (i);
}
