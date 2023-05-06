/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_parse_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:28:16 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/06 21:07:33 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data(t_map *data)
{
	data->map_height = 0;
	data->map_width = 0;
	data->player_cnt = 0;
	data->floor_color = -1;
	data->ceil_color = -1;
	data->path_north = NULL;
	data->path_south = NULL;
	data->path_west = NULL;
	data->path_east = NULL;
	data->file = NULL;
}

int is_texture(char *line)
{
	 if(ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "NO ", 3) == 0
			|| ft_strncmp(line, "SO ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
				return (1);
	return (0);			
}

int is_color(char *line)
{
	 if(ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
				return (1);
	return (0);			
}

void	is_valid_xpm(const char *path, t_map *map)
{
	int			index;
	const int	exten = 4;
	index = (int) ft_strlen(path) - exten;
	if (index < 0 || 
			ft_strncmp(".xpm", (char *)(path + index), exten + 1))
		put_error("invalid xpm file", map);
}

void is_valid_path(char *path, t_map *map)
{
	int fd;
	
	fd = open(path, O_RDONLY);
	if (fd < 0)
		free(path), put_error("Bad texture's file", map);
	is_valid_xpm(path, map);
}