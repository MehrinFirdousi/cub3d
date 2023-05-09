/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 23:50:50 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/09 23:55:41 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


static char	*bonus_path_substr(const char *line, t_map *map)
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

static void bonus_update_flag(int *flag, const char *line)
{
	if (ft_strncmp(line, "DO ", 3) == 0)
		*flag = (9);
	if (ft_strncmp(line, "F1 ", 3) == 0)
		*flag = (1);
	if (ft_strncmp(line, "F2 ", 3) == 0)
		*flag = (2);
	if (ft_strncmp(line, "F3 ", 3) == 0)
		*flag = (3);
	if (ft_strncmp(line, "F4 ", 3) == 0)
		*flag = (4);
	if (ft_strncmp(line, "F5 ", 3) == 0)
		*flag = (5);
	if (ft_strncmp(line, "F6 ", 3) == 0)
		*flag = (6);
	if (ft_strncmp(line, "F7 ", 3) == 0)
		*flag = (7);
	if (ft_strncmp(line, "F8 ", 3) == 0)
		*flag = (8);
}

void	get_textures1(const char *line, t_map *data)
{
	int		flag;
	char	*path;
	char	*tmp_path;

	tmp_path = bonus_path_substr(&line[3], data);
	path = ft_strtrim(tmp_path, " \t");
	free(tmp_path);
	is_valid_path(path, data);
	flag = 0;	
	bonus_update_flag(&flag, line);
	if (flag == 9 && !data->door)
		data->door = path;
	else if (flag == 1 && !data->f1)
		data->f1 = path;
	else if (flag == 2 && !data->f2)
		data->f2 = path;
	else if (flag == 3 && !data->f3)
		data->f3 = path;
	else if (flag == 4 && !data->f4)
		data->f4 = path;
	else if (flag == 5 && !data->f5)
		data->f5 = path;
	else if (flag == 6 && !data->f6)
		data->f6 = path;
	else if (flag == 7 && !data->f7)
		data->f7 = path;
	else if (flag == 8 && !data->f8)
		data->f8 = path;	
	else
		put_error("Dublicate flame side", data);
}

int is_extra_texture(char *line)
{
	 if(ft_strncmp(line, "DO ", 3) == 0 || ft_strncmp(line, "F1 ", 3) == 0
			|| ft_strncmp(line, "F2 ", 3) == 0 || ft_strncmp(line, "F3 ", 3) == 0
			|| ft_strncmp(line, "F4 ", 3) == 0 || ft_strncmp(line, "F5 ", 3) == 0
			|| ft_strncmp(line, "F6 ", 3) == 0 || ft_strncmp(line, "F7 ", 3) == 0
			|| ft_strncmp(line, "F8 ", 3) == 0)
				return (1);
	return (0);			
}

static int is_valid_data(int *i, char *line, t_map *data)
{
	while (line[*i] != '\0')
	{
		while (line[*i] && ft_is_space(line[*i]))
			(*i)++;
		if (data->texture_cnt == 9 && is_extra_texture(&line[*i]))
			return 0;
		if(is_extra_texture(&line[*i]))
		{
			get_textures1(&line[*i], data);
			data->texture_cnt++;
		}
		else
			break ;
		*i += cur_index(&line[*i], '\n');
	}
	return (*i);
}

int valid_extra_textures(char *line, t_map *data)
{
	int	i;

	i = 0;
	data->texture_cnt = 0;
	data->color_cnt = 0;

	if (!is_valid_data(&i, line, data))
		return i;
	if(data->texture_cnt != 9)
		put_error("Invalid data", data);
	if (line[i] == '\0')
		put_error("Map is missing one or more data", data);
	return (i);
}