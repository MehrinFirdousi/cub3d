/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 08:56:25 by ahassan           #+#    #+#             */
/*   Updated: 2023/04/30 17:11:58 by ahassan          ###   ########.fr       */
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
	int i;
	
	data = NULL;
	init_data(&data);
	i = convert_texture(line, data, 0);
	i += convert_texture(&line[i], data, 1);
	get_map(&line[i], data);

	while(*data->map)
		printf("{%s}\n", *data->map++);
	return (data);
}


//pa = 270 NORTH
// == 90 West