/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 18:00:59 by mfirdous          #+#    #+#             */
/*   Updated: 2023/05/01 22:38:15 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	draw_fov(t_mlx *m)
{
	int	ray_no;

	ray_no = -1;
	while (++ray_no < WIN_WIDTH)
		dda(m, (t_point){m->p->px, m->p->py},
			(t_point){m->rays[ray_no].x, m->rays[ray_no].y}, TEAL);
}

int	get_block_color(t_map *m, int i, int j)
{
	if (m->map[i][j] == '1')
	{
		if (j >= 0 && i >= 0 && j < m->map_width - 1 && i < m->map_height - 1 \
			&& (m->map[i + 1][j] == 'O' || m->map[i][j + 1] == 'O'))
			return (ORANGE);
		if (j > 0 && i > 0 && j < m->map_width && i < m->map_height \
			&& (m->map[i - 1][j] == 'O' || m->map[i][j - 1] == 'O'))
			return (ORANGE);
		return (WHITE);
	}
	else if (m->map[i][j] == 'D')
		return (BLUE);
	return (GRAY);
}

void	draw_minimap(t_mlx *m)
{
	int	i;
	int	j;
	int	x;
	int	y;
	int	color;

	i = -1;
	while (++i < m->map->map_height)
	{
		j = -1;
		while (++j < m->map->map_width)
		{
			x = j << SHIFT_VALUE;
			y = i << SHIFT_VALUE;
			color = get_block_color(m->map, i, j);
			draw_square(m, (t_point){x, y}, MM_SIZE, color);
		}
	}
	draw_square(m, (t_point){m->p->px, m->p->py}, 3, GREEN);
	draw_fov(m);
}
