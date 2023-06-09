/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 15:09:47 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/15 17:02:24 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	is_valid_file(const char *file_name, const char *file_exten, t_map *map)
{
	int	index;

	index = (int)ft_strlen(file_name) - FILE_EXTEN;
	if (index < 0
		|| ft_strncmp(file_exten, (char *)(file_name + index), FILE_EXTEN + 1))
		put_error("Invalid file", map);
}

static char	*read_file(int fd, t_map *map)
{
	int		i;
	char	*line;
	char	*result;

	result = ft_strdup("");
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line && i == 0)
			return (free(result), put_error("Is Empty", map), NULL);
		if (!line)
			break ;
		result = ft_strjoin(result, line);
		free(line);
		i++;
	}
	return (result);
}

void	parsing(int argc, char **argv, t_map *map, t_player *p)
{
	int		fd;
	char	*rd;

	if (argc != 2)
		put_error("invalid arguments", map);
	is_valid_file(argv[1], ".cub", map);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		put_error("invalid file | rights", map);
	rd = read_file(fd, map);
	close(fd);
	map->file = rd;
	get_data(rd, map, p);
}
