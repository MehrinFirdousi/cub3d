/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 15:09:47 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/03 19:58:03 by ahassan          ###   ########.fr       */
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

static char	*read_data(int fd)
{
	int		rd;
	char	buff[1 + 1];
	char	*text;
	char	*result;

	text = ft_strdup("");
	if (!text)
		put_error("allocating memory err");
	rd = read(fd, buff, 1);
	if (rd == 0)
		put_error("is empty");
	while (*buff != '\0' && rd > 0)
	{
		buff[rd] = '\0';
		result = ft_strjoin(text, buff);
		if (!result)
			put_error("allocating memory err");
		free(text);
		text = result;
		rd = read(fd, buff, 1);
	}
	if (rd < 0)
		put_error("read file error");
	return (result);
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
	rd = read_data(fd);
	close(fd);
	get_data(rd, map, p);
}
