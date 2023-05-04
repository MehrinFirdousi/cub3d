/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 10:25:06 by ahassan           #+#    #+#             */
/*   Updated: 2023/05/04 14:47:50 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	valid_color(const char *str)
{
	int	num;
	int i;
	
	i = 0;
	if(!str[i])
		put_error("NULL color");
	while (str[i] == ' ')
		i++;
	num = 0;
	if(!str[i])
		put_error("NULL color");
	while (ft_isdigit(str[i]))
	{
		num = num * 10 + (str[i++] - '0');
		if(num > 255)
			return -1;
	}
	while (str[i] == ' ')
		++str;
	if (str[i] != '\0' && str[i] != ',' && str[i] != '\n')
		put_error("Not valid colors");
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

void	put_error(const char *error)
{
	write(2, "ERROR\n", ft_strlen("ERROR\n"));
	write(2, error, ft_strlen(error));
	write(2, "\n", 1);
	exit(1);
}

void print_map(t_map *map, t_player *p)
{
	int i;

	i = 0;
	printf("py == %lf\n", p->py);
	printf("px == %lf\n", p->px);
	printf("pa == %lf\n", p->pa);
	while(map->map[i])
		ft_printf("{%s}\n", map->map[i++]);
}

int	check_surface(const char *line)
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
		put_error("Undefined side");
	return (-1);
}