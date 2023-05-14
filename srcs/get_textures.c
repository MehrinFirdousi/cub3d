/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:38:58 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/14 15:57:10 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*path_substr(const char *line, t_map *map)
{
	int	i;

	while (ft_is_space(*line))
		++line;
	if (*line == '\0')
		put_error("No path", map);
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		++i;
	return (ft_substr(line, 0, i));
}

static void	update_flag(int *flag, const char *line)
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

void	get_textures(const char *line, t_map *data)
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
	if (flag == E_NORTH && !data->n_texture.path)
		data->n_texture.path = path;
	else if (flag == E_SOUTH && !data->s_texture.path)
		data->s_texture.path = path;
	else if (flag == E_WEST && !data->w_texture.path)
		data->w_texture.path = path;
	else if (flag == E_EAST && !data->e_texture.path)
		data->e_texture.path = path;
	else
	{
		free(path);
		put_error("Duplicate path side", data);
	}
}
