/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 01:47:33 by mfirdous          #+#    #+#             */
/*   Updated: 2023/05/02 01:47:33 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_horizontal_intersect(t_player *p, t_ray *r)
{
	r->dof = 0;
	r->tan_ra = -(1 / tan(r->ra));
	if (r->ra > M_PI) // looking up
	{
		r->ry = (((int)p->py / BLOCK_SIZE) * BLOCK_SIZE) - 0.0001; // rounding the ray's y position to the nearest BLOCK_SIZEth value
		r->rx = (p->py - r->ry) * r->tan_ra + p->px;
		r->y_step = -BLOCK_SIZE;
		r->x_step = -r->y_step * r->tan_ra;
	}
	else if (r->ra < M_PI) // looking down
	{
		r->ry = (((int)p->py / BLOCK_SIZE) * BLOCK_SIZE) + BLOCK_SIZE; // rounding the ray's y position to the nearest BLOCK_SIZEth value
		r->rx = (p->py - r->ry) * r->tan_ra + p->px;
		r->y_step = BLOCK_SIZE;
		r->x_step = -r->y_step * r->tan_ra;
	}
	else // ray is exactly facing right or left
	{
		r->rx = p->px;
		r->ry = p->py;
		r->dof = r->max_dof;
	}
}

static void	check_vertical_intersect(t_player *p, t_ray *r)
{
	r->dof = 0;
	r->tan_ra = -tan(r->ra);
	if (r->ra > M_PI / 2 && r->ra < 3 * M_PI / 2) // looking left - >90 and <270
	{
		r->rx = (((int)p->px / BLOCK_SIZE) * BLOCK_SIZE) - 0.0001; // rounding the ray's y position to the nearest BLOCK_SIZEth value
		r->ry = (p->px - r->rx) * r->tan_ra + p->py;
		r->x_step = -BLOCK_SIZE;
		r->y_step = -r->x_step * r->tan_ra;
	}
	else if (r->ra < M_PI / 2 || r->ra > 3 * M_PI / 2) // looking right
	{
		r->rx = (((int)p->px / BLOCK_SIZE) * BLOCK_SIZE) + BLOCK_SIZE; // rounding the ray's y position to the nearest BLOCK_SIZEth value
		r->ry = (p->px - r->rx) * r->tan_ra + p->py;
		r->x_step = BLOCK_SIZE;
		r->y_step = -r->x_step * r->tan_ra;
	}
	else // ray is exactly facing right or left
	{
		r->rx = p->px;
		r->ry = p->py;
		r->dof = r->max_dof;
	}
}

// casts a ray till it hits a wall
static void	cast_ray(t_map *m, t_ray *r)
{
	int	mx;
	int	my;

	while (r->dof < r->max_dof)
	{
		// finding the ray hit position in the map array
		mx = (int)r->rx / BLOCK_SIZE;
		my = (int)r->ry / BLOCK_SIZE;
		// printf("ray facing (%d, %d)\n", my, mx);
		if (mx >= 0 && my >= 0 && mx < m->map_width && my < m->map_height \
			&& m->map[my][mx] == '1') // if we hit a wall
			break;
		else
		{
			r->rx += r->x_step;
			r->ry += r->y_step;
			r->dof++;
		}
	}
}

static void	draw_scene(t_mlx *m, t_ray *r, int ray_no, int color)
{
	double	line_height;
	double	line_offset;
	double	a_diff;		// angle difference between player angle and ray angle
						// used to fix unwanted fisheye effect

	// 3d ray 
	a_diff = fix_angle(m->pos->pa - r->ra);
	r->ray_len = r->ray_len * cos(a_diff);
	line_height = (BLOCK_SIZE * WIN_HEIGHT) / r->ray_len;
	line_offset = WIN_HEIGHT / 2 - line_height / 2;
	// dda(m, (t_point){ray_no, line_offset}, (t_point){ray_no, line_height + line_offset}, ray_no, line_offset, ray_no, line_height + line_offset, color);
	dda(m, (t_point){ray_no, 0}, (t_point){ray_no, line_offset}, m->map->ceil_color);
	dda(m, (t_point){ray_no, line_offset}, (t_point){ray_no, line_height + line_offset}, color);
	dda(m, (t_point){ray_no, line_height + line_offset}, (t_point){ray_no, WIN_HEIGHT}, m->map->floor_color);
	
	// 2d ray for minimap
	dda(m, (t_point){m->pos->px, m->pos->py}, (t_point){r->rx, r->ry}, color);
}

void draw_rays_2d(t_mlx* m)
{
	double	ra; // ray angle
	int		i;
	t_ray	h_ray;
	t_ray	v_ray;
	
	i = -1;
	ra = fix_angle(m->pos->pa - ONEDEG * WIN_WIDTH / 2); // move the ray angle back by 30 degrees
	h_ray.max_dof = m->map->map_height;
	v_ray.max_dof = m->map->map_width;
	while (++i < WIN_WIDTH)
	{
		h_ray.ra = ra;
		v_ray.ra = ra;
		check_horizontal_intersect(m->pos, &h_ray);
		cast_ray(m->map, &h_ray);
		h_ray.ray_len = get_ray_len(m->pos->px, m->pos->py, h_ray.rx, h_ray.ry);
		check_vertical_intersect(m->pos, &v_ray);
		cast_ray(m->map, &v_ray);
		v_ray.ray_len = get_ray_len(m->pos->px, m->pos->py, v_ray.rx, v_ray.ry);
		if (h_ray.ray_len <= v_ray.ray_len) // ray hit a horizontal wall
			draw_scene(m, &h_ray, i, TEAL);
		else // ray hit a vertical wall
			draw_scene(m, &v_ray, i, TEAL_D);
		ra = fix_angle(ra + ONEDEG);
	}
}