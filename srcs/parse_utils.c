/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:25:06 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/10 00:39:39 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_color(const char *str)
{
	int	num;
	int i;
	
	i = 0;
	if(!str[i])
		return -1;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	num = 0;
	if(!str[i])
		return -1;
	while (ft_isdigit(str[i]))
	{
		num = num * 10 + (str[i++] - '0');
		if(num > 255)
			return -1;
	}
	while (str[i] == ' ' || str[i] == '\t')
		++str;
	if (str[i] != '\0' && str[i] != ',' && str[i] != '\n')
		return -1;
	return (num);
}

int	cur_index(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		++i;
	return (i);
}

static void free_malloced(t_map *map)
{
	if(map->n_texture.path)
		free(map->n_texture.path);
	if(map->s_texture.path)
		free(map->s_texture.path);
	if(map->w_texture.path)
		free(map->w_texture.path);
	if(map->e_texture.path)
		free(map->e_texture.path);
	if(map->file)
		free(map->file);
	int i = 0;	
	while(i < map->map_height)
			free(map->map[i++]);
	if(map->map_height)		
		free(map->map);
}

void	put_error(const char *error, t_map *map)
{
	write(2, "ERROR\n", ft_strlen("ERROR\n"));
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	free_malloced(map);
	exit(1);
}

void print_map(t_map *map, t_player *p)
{
	int i;

	i = 0;
	printf("height == %d\n", map->map_height);
	printf("width == %d\n", map->map_width);
	printf("py == %lf\n", p->py);
	printf("px == %lf\n", p->px);
	printf("pa == %lf\n", p->pa);
	printf("{%s}\n", map->n_texture.path);
	printf("{%s}\n", map->s_texture.path);
	printf("{%s}\n", map->w_texture.path);
	printf("{%s}\n", map->e_texture.path);
	printf("Door {%s}\n", map->c_door_texture.path);
	printf("T1 {%s}\n", map->torch[0].path);
	printf("T2 {%s}\n", map->torch[1].path);
	printf("T3 {%s}\n", map->torch[2].path);
	printf("T4 {%s}\n", map->torch[3].path);
	printf("T5 {%s}\n", map->torch[4].path);
	printf("T6 {%s}\n", map->torch[5].path);
	printf("T7 {%s}\n", map->torch[6].path);
	printf("T8 {%s}\n", map->torch[7].path);
	while(map->map[i])
		ft_printf("{%s}\n", map->map[i++]);
}

int	check_surface(const char *line, t_map *map)
{	
	int i;

	i = 0;
	while(line[i] && line[i] == ' ')
		i++;
	if (ft_strncmp(&line[i], "F ", 2) == 0)
		return (E_FLOOR);
	else if (ft_strncmp(&line[i], "C ", 2) == 0)
		return (E_CEIL);
	else
		put_error("Undefined side", map);
	return (-1);
}