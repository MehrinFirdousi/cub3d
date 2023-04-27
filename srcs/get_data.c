/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_data.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 08:56:25 by ahassan           #+#    #+#             */
/*   Updated: 2023/04/27 16:53:46 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub.h"

void	put_error(const char *error)
{
	write(2, "ERROR\n", ft_strlen("ERROR\n"));
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	exit(1);
}

int	get_index(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		++i;
	return (i);
}

char	*path_substr(const char *line)
{
	int		i;
	// printf("{%s}", line); //heap over flow on loop 4
	while (*line == ' ')
		++line;
	if (*line == '\0')
		put_error("no path");
	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		++i;
	return ft_substr(line, 0, i);
}

void	get_paths(const char *line, t_data *data)
{
	int		flag;
	char	*path;
	
	path = path_substr(&line[3]);

	if (ft_strncmp(line, "NO ", 3) == 0)
		flag = (E_NORTH);
	if (ft_strncmp(line, "SO ", 3) == 0)
		flag =  (E_SOUTH);
	if (ft_strncmp(line, "WE ", 3) == 0)
		flag =  (E_WEST);
	if (ft_strncmp(line, "EA ", 3) == 0)
		flag =  (E_EAST);

	printf("flag  %d\n", flag);
	if (flag == E_NORTH && !data->path_north)
		data->path_north = path;
	else if (flag == E_SOUTH && !data->path_south)
		data->path_south = path;
	else if (flag == E_WEST && !data->path_west)
		data->path_west = path;
	else if (flag == E_EAST && !data->path_east)
		data->path_east = path;
	else{
		printf("flag %d\n", flag);
		put_error("Side not recognized");
	}
}

int	convert_texture(char *line, t_data *data)
{
	int	i;
	int	count_line;

	i = 0;
	count_line = 0;
	int loop = 0;
	while (line[i] != '\0')
	{
		loop++;
		printf("loop %d\n", loop); //heap over flow on loop 4
		while (line[i] == '\n')
			++i;
		if (count_line == 4)
			return (i);
		get_paths(&line[i], data);
		++count_line;
		i += get_index(&line[i], '\n');
	}
	return (i);
}

t_data	*get_data(char *line)
{
	t_data	*data;

	data = (t_data *) malloc(sizeof (t_data));
	data->path_north = NULL;
	data->path_south = NULL;
	data->path_west = NULL;
	data->path_east = NULL;

	convert_texture(line, data);
	
	return (data);
}
