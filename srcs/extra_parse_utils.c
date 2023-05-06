/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_parse_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 15:28:16 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/06 15:33:52 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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