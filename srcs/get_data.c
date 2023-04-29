/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 08:56:25 by ahassan           #+#    #+#             */
/*   Updated: 2023/04/29 23:03:56 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_map **data)
{
	*data = (t_map *) malloc(sizeof (t_map));
	(*data)->path_north = NULL;
	(*data)->path_south = NULL;
	(*data)->path_west = NULL;
	(*data)->path_east = NULL;
}

t_map	*get_data(char *line)
{
	t_map	*data;

	data = NULL;
	init_data(&data);
	convert_texture(&line[convert_texture(line, data, 0)], data, 1);
	printf("%d\n", data->floor_color);
	printf("%d\n", data->ceil_color);

	return (data);
}
