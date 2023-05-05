/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_upper_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:29:30 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/01 23:08:47 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void is_valid_path(char *path, t_map *map)
{
	int fd;
	
	fd = open(path, O_RDONLY);
	if (fd < 0)
		free(path), put_error("Bad texture's file", map);
}

static char	*path_substr(const char *line, t_map *map)
{
	int		i;
	while (ft_is_space(*line))
		++line;
	if (*line == '\0')
		put_error("No path", map);
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
	char	*tmp_path;

	tmp_path = path_substr(&line[3], data);
	path = ft_strtrim(tmp_path, " \t");
	free(tmp_path);
	is_valid_path(path, data);
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
		put_error("Side not recognized", data);
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

int	get_upper_map(char *line, t_map *data)
{
	int	i;
	int	count_line;
	int	count_color;

	i = 0;
	count_line = 0;
	count_color = 0;
	while (line[i] != '\0')
	{
		while (line[i] && ft_is_space(line[i]))
			++i;
		if (count_line == 4 && is_texture(&line[i]))
			return (i);
		if (count_color == 2 && is_color(&line[i]))
			return (i);
		if(is_texture(&line[i]))
		{
			get_paths(&line[i], data);
			count_line++;
		}
		else if (is_color(&line[i]))
		{
			get_colors(&line[i], data);	
			count_color++;
		}
		else
			break ;
		i += cur_index(&line[i], '\n');
	}
	if(count_color != 2 || count_line != 4)
		put_error("Wrong amount of data", data);
	if (line[i] == '\0')
		put_error("Map is missing one or more data", data);
	return (i);
}