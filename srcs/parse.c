/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 15:09:47 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/04 22:03:13 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	is_valid_file(const char *file_name, t_map *map)
{
	int			index;
	const int	exten = 4;

	index = (int) ft_strlen(file_name) - exten;
	if (index < 0 || 
			ft_strncmp(".cub", (char *)(file_name + index), exten + 1))
		put_error("invalid file", map);
}

static char *read_file(int fd, t_map *map)
{
	int i;
	char *line;
	char *result;
	
	result = ft_strdup("");
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line && i == 0)
			return free(result), put_error("Is Empty", map), NULL;;
		if (!line)
			break;
		result = ft_strjoin(result, line);
		free(line);
		i++;
	}
	return result;
}

void	parsing(int argc, char **argv, t_map *map, t_player *p)
{
	int		fd;
	char	*rd;

	if (argc != 2)
		put_error("invalid arguments", map);
	is_valid_file(argv[1], map);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		put_error("invalid file | rights", map);
	rd = read_file(fd, map);
	close(fd);
	map->file = rd;
	get_data(rd, map, p);
}
