/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_data.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:29:30 by ahassan           #+#    #+#             */
/*   Updated: 2023/04/28 11:06:41 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void is_valid_path(char *path)
{
	int fd;
	
	fd = open(path, O_RDONLY);
	if (fd < 0)
		put_error("Bad texture's file");
}

static char	*path_substr(const char *line)
{
	int		i;
	while (*line == ' ')
		++line;
	if (*line == '\0')
		put_error("No path");
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		++i;
	return (ft_substr(line, 0, i));
}

static void update_flag(int *flag, const char *line)
{
	if (!ft_strncmp(line, "NO ", 3))
		*flag = (E_NORTH);
	if (!ft_strncmp(line, "SO ", 3))
		*flag = (E_SOUTH);
	if (!ft_strncmp(line, "WE ", 3))
		*flag = (E_WEST);
	if (!ft_strncmp(line, "EA ", 3))
		*flag = (E_EAST);
}

static void	get_paths(const char *line, t_map *data)
{
	int		flag;
	char	*path;

	path = path_substr(&line[3]);
	is_valid_path(path);
	flag = -1;	
	update_flag(&flag, line);
	if (flag == E_NORTH && !data->path_north)
		data->path_north = path;
	else if (flag == E_SOUTH && !data->path_south)
		data->path_south = path;
	else if (flag == E_WEST && !data->path_west)
		data->path_west = path;
	else if (flag == E_EAST && !data->path_east)
		data->path_east = path;
	else
		put_error("Side not recognized");
}

int	convert_texture(char *line, t_map *data)
{
	int	i;
	int	count_line;

	i = 0;
	count_line = 0;
	while (line[i] != '\0')
	{
		while (line[i] == '\n')
			++i;
		if (count_line == 4)
			return (i);
		get_paths(&line[i], data);
		++count_line;
		i += cur_index(&line[i], '\n');
	}
	return (i);
}