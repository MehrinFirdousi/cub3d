/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 15:09:47 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/04 15:03:10 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	is_valid_file(const char *file_name)
{
	int			index;
	const int	exten = 4;

	index = (int) ft_strlen(file_name) - exten;
	if (index < 0 || 
			ft_strncmp(".cub", (char *)(file_name + index), exten + 1))
		put_error("invalid file");
}

static char *read_file(int fd)
{
	int i;
	char *line;
	char *result;
	char	*text;
	
	i = 0;
	text = ft_strdup("");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		result = ft_strjoin(text, line);
		free(text);
		text = result;
		i++;
	}
	if(!result)
		return put_error("Is Empty"), NULL;
	return result;
}

void	parsing(int argc, char **argv, t_map *map, t_player *p)
{
	int		fd;
	char	*rd;

	if (argc != 2)
		put_error("invalid arguments");
	is_valid_file(argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		put_error("invalid file | rights");
	rd = read_file(fd);
	close(fd);
	get_data(rd, map, p);
}
