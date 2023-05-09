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

// checks if the ray is facing up or down and calculates the step value
static void	check_horizontal_intersect(t_player *p, t_ray *r)
{
	r->dof = 0;
	r->tan_ra = -(1 / tan(r->ra));
	if (r->ra > M_PI)
	{
		r->ry = (((int)p->py / BLOCK_SIZE) * BLOCK_SIZE) - 0.0001;
		r->rx = (p->py - r->ry) * r->tan_ra + p->px;
		r->y_step = -BLOCK_SIZE;
		r->x_step = -r->y_step * r->tan_ra;
	}
	else if (r->ra < M_PI)
	{
		r->ry = (((int)p->py / BLOCK_SIZE) * BLOCK_SIZE) + BLOCK_SIZE;
		r->rx = (p->py - r->ry) * r->tan_ra + p->px;
		r->y_step = BLOCK_SIZE;
		r->x_step = -r->y_step * r->tan_ra;
	}
	else
	{
		r->rx = p->px;
		r->ry = p->py;
		r->dof = r->max_dof;
	}
}

// checks if the ray is facing left or right and calculates the step value
static void	check_vertical_intersect(t_player *p, t_ray *r)
{
	r->dof = 0;
	r->tan_ra = -tan(r->ra);
	if (r->ra > M_PI / 2 && r->ra < 3 * M_PI / 2)
	{
		r->rx = (((int)p->px / BLOCK_SIZE) * BLOCK_SIZE) - 0.0001;
		r->ry = (p->px - r->rx) * r->tan_ra + p->py;
		r->x_step = -BLOCK_SIZE;
		r->y_step = -r->x_step * r->tan_ra;
	}
	else if (r->ra < M_PI / 2 || r->ra > 3 * M_PI / 2)
	{
		r->rx = (((int)p->px / BLOCK_SIZE) * BLOCK_SIZE) + BLOCK_SIZE;
		r->ry = (p->px - r->rx) * r->tan_ra + p->py;
		r->x_step = BLOCK_SIZE;
		r->y_step = -r->x_step * r->tan_ra;
	}
	else
	{
		r->rx = p->px;
		r->ry = p->py;
		r->dof = r->max_dof;
	}
}

// casts a ray till it hits a wall
static void	cast_ray(t_map *m, t_ray *r, bool is_vertical)
{
	int	mx;
	int	my;

	r->door_status = 0;
	r->vertical = is_vertical;
	while (r->dof < r->max_dof)
	{
		mx = (int)r->rx / BLOCK_SIZE;
		my = (int)r->ry / BLOCK_SIZE;
		if (mx >= 0 && my >= 0 && mx < m->map_width && my < m->map_height \
			&& m->map[my][mx] == '1')
		{
			if (is_vertical)
			{
				if (mx > 0 && my >= 0 && mx < m->map_width - 1 && my < m->map_height \
					&& (m->map[my][mx + 1] == 'O' || m->map[my][mx - 1] == 'O'))
					r->door_status = 2;
			}
			else
			{
				if (mx >= 0 && my > 0 && mx < m->map_width && my < m->map_height - 1 \
					&& (m->map[my + 1][mx] == 'O' || m->map[my - 1][mx] == 'O'))
					r->door_status = 3;
			}
			break ;
		}
		if (mx >= 0 && my >= 0 && mx < m->map_width && my < m->map_height \
			&& m->map[my][mx] == 'D')
		{
			r->door_status = 1;
			break;
		}
		else
		{
			r->rx += r->x_step;
			r->ry += r->y_step;
			r->dof++;
		}
	}
}

// draws one vertical line from the ray, constituting the 3d scene
static void	draw_ray(t_mlx *m, t_ray *r, int ray_no, bool is_vertical)
{
	int		i;
	double	line_height;
	double	line_offset;
	double	a_diff;

	r->vertical = is_vertical;
	a_diff = fix_angle(m->p->pa - r->ra);
	r->ray_len = r->ray_len * cos(a_diff);
	line_height = (BLOCK_SIZE * WIN_HEIGHT) / r->ray_len;
	line_offset = WIN_HEIGHT / 2 - line_height / 2;
	i = -1;
	while (++i < line_offset)
		my_mlx_pixel_put(m->img, ray_no, i, m->map->ceil_color);
	if (ray_no > 0)
		draw_texture(m, r, (t_point){ray_no, line_offset}, line_height);
	i = line_height + line_offset - 1;
	while (++i < WIN_HEIGHT)
		my_mlx_pixel_put(m->img, ray_no, i, m->map->floor_color);
	m->rays[ray_no].x = r->rx;
	m->rays[ray_no].y = r->ry;
}

void	draw_scene(t_mlx *m)
{
	double		ra;
	int			i;
	t_ray		h_ray;
	t_ray		v_ray;

	i = -1;
	ra = fix_angle(m->p->pa - ANGLE_STEP * WIN_WIDTH / 2);
	h_ray.max_dof = m->map->map_height;
	v_ray.max_dof = m->map->map_width;
	while (++i < WIN_WIDTH)
	{
		h_ray.ra = ra;
		v_ray.ra = ra;
		check_horizontal_intersect(m->p, &h_ray);
		cast_ray(m->map, &h_ray, false);
		h_ray.ray_len = get_ray_len(m->p->px, m->p->py, h_ray.rx, h_ray.ry);
		check_vertical_intersect(m->p, &v_ray);
		cast_ray(m->map, &v_ray, true);
		v_ray.ray_len = get_ray_len(m->p->px, m->p->py, v_ray.rx, v_ray.ry);
		if (h_ray.ray_len <= v_ray.ray_len)
			draw_ray(m, &h_ray, i, false);
		else
			draw_ray(m, &v_ray, i, true);
		ra = fix_angle(ra + ANGLE_STEP);
	}
}
