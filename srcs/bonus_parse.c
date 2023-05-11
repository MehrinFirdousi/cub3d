/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 23:50:50 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/11 20:55:18 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	bonus_update_flag(int *flag, const char *line)
{
	if (ft_strncmp(line, "DO ", 3) == 0)
		*flag = (7);
	if (ft_strncmp(line, "T1 ", 3) == 0)
		*flag = (1);
	if (ft_strncmp(line, "T2 ", 3) == 0)
		*flag = (2);
	if (ft_strncmp(line, "T3 ", 3) == 0)
		*flag = (3);
	if (ft_strncmp(line, "T4 ", 3) == 0)
		*flag = (4);
	if (ft_strncmp(line, "T5 ", 3) == 0)
		*flag = (5);
	if (ft_strncmp(line, "T6 ", 3) == 0)
		*flag = (6);
}

static char	*get_path(int *flag, char *line, t_map *data)
{
	char	*path;
	char	*tmp_path;

	tmp_path = path_substr(&line[3], data);
	path = ft_strtrim(tmp_path, " \t");
	free(tmp_path);
	is_valid_path(path, data);
	*flag = 0;
	bonus_update_flag(flag, line);
	return (path);
}

static void	get_extra_textures(char *line, t_map *data)
{
	int		flag;
	int		i;
	char	*path;

	path = get_path(&flag, line, data);
	i = -1;
	while (++i < FRAME_TOTAL)
	{
		if (flag == (FRAME_TOTAL + 1) && !data->c_door_texture.path)
		{
			data->c_door_texture.path = path;
			return ;
		}
		if (flag == (i + 1) && !data->torch[i].path)
		{
			data->torch[i].path = path;
			return ;
		}
	}
	free(path);
	put_error("Duplicate flame side", data);
}

static int	is_extra_texture(char *line)
{
	if (ft_strncmp(line, "DO ", 3) == 0 || ft_strncmp(line, "T1 ", 3) == 0
		|| ft_strncmp(line, "T2 ", 3) == 0 || ft_strncmp(line, "T3 ", 3) == 0
		|| ft_strncmp(line, "T4 ", 3) == 0 || ft_strncmp(line, "T5 ", 3) == 0
		|| ft_strncmp(line, "T6 ", 3) == 0)
		return (1);
	return (0);
}

static int	is_valid_data(int *i, char *line, t_map *data)
{
	while (line[*i] != '\0')
	{
		while (line[*i] && ft_is_space(line[*i]))
			(*i)++;
		if (data->texture_cnt == FRAME_TOTAL + 1 && is_extra_texture(&line[*i]))
			return (0);
		if (is_extra_texture(&line[*i]))
		{
			get_extra_textures(&line[*i], data);
			data->texture_cnt++;
		}
		else
			break ;
		*i += cur_index(&line[*i], '\n');
	}
	return (*i);
}

int	valid_extra_textures(char *line, t_map *data)
{
	int i;

	i = 0;
	data->texture_cnt = 0;
	data->color_cnt = 0;

	if (!is_valid_data(&i, line, data))
		return (i);
	if (data->texture_cnt != FRAME_TOTAL + 1)
		put_error("Invalid data", data);
	if (line[i] == '\0')
		put_error("Map is missing one or more data", data);
	return (i);
}