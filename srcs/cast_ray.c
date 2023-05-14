/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 20:10:36 by mfirdous          #+#    #+#             */
/*   Updated: 2023/05/14 20:21:53 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	is_within_map_boundaries(int x, int y, t_map *m, int os)
{
	if (x > -1 + os && y > -1 + os
		&& x < m->map_width - os && y < m->map_height - os)
		return (true);
	return (false);
}

static bool	hit_wall(int mx, int my, t_map *m, t_ray *r)
{
	if (is_within_map_boundaries(mx, my, m, 0) && m->map[my][mx] == '1')
	{
		if (r->vertical)
		{
			if (mx > 0 && my >= 0 && mx < m->map_width - 1 && my < m->map_height
				&& (m->map[my][mx + 1] == 'O' || m->map[my][mx - 1] == 'O'))
				r->door_status = 2;
		}
		else
		{
			if (mx >= 0 && my > 0 && mx < m->map_width && my < m->map_height - 1
				&& (m->map[my + 1][mx] == 'O' || m->map[my - 1][mx] == 'O'))
				r->door_status = 3;
		}
		return (true);
	}
	else if (is_within_map_boundaries(mx, my, m, 0) && m->map[my][mx] == 'D')
	{
		r->door_status = 1;
		return (true);
	}
	return (false);
}

// casts a ray till it hits a wall
void	cast_ray(t_map *m, t_ray *r, bool is_vertical)
{
	int	mx;
	int	my;

	r->door_status = 0;
	r->vertical = is_vertical;
	while (r->dof < r->max_dof)
	{
		mx = (int)r->rx >> SHIFT_VALUE;
		my = (int)r->ry >> SHIFT_VALUE;
		if (hit_wall(mx, my, m, r))
			break ;
		else
		{
			r->rx += r->x_step;
			r->ry += r->y_step;
			r->dof++;
		}
	}
}
