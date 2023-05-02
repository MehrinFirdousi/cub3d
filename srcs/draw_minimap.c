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


void draw_minimap(t_mlx *m)
{
	int	i;
	int	j;
	int x;
	int y;
	int color;

	i = -1;
	color = GRAY;
	while (++i < m->map->map_height)
	{
		j = -1;
		while (++j < m->map->map_width)
		{
			x = j * 16;
			y = i * 16;
			if (m->map->map[i][j] == '1')
				color = WHITE;
			draw_square(m, (t_point){x, y}, 16, color);
			/*dda(m, (t_point){x + 1, y + 1}, \
					(t_point){x + 1, y + 16 - 1},
					color);
			dda(m, (t_point){x + 1, y + 16 - 1}, \
					(t_point){x + 16 - 1, y + 16 - 1},
					color);
			dda(m, (t_point){x + 16 - 1, y + 16 - 1}, \
					(t_point){x + 16 - 1, y + 1},
					color);
			dda(m, (t_point){x + 16 - 1, y + 1}, \
					(t_point){x + 1, y + 1},
					color);*/
			if (m->map->map[i][j] == 'N')
			{
				color = GREEN;
				my_mlx_pixel_put(m->img, m->pos->px, m->pos->py, color);
				my_mlx_pixel_put(m->img, m->pos->px + 1, m->pos->py, color);
				my_mlx_pixel_put(m->img, m->pos->px + 1, m->pos->py + 1, color);
				my_mlx_pixel_put(m->img, m->pos->px, m->pos->py + 1, color);
				dda(m,(t_point){m->pos->px, m->pos->py}, (t_point){m->pos->px + (m->pos->pdx * 5), m->pos->py + (m->pos->pdy * 5)}, color);
				// dda(m, m->pos->px, m->pos->py, m->pos->px + (m->pos->pdx * 5), m->pos->py + (m->pos->pdy * 5), color);
			}
			color = GRAY;
		}
	}
}