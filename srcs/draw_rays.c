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
		r->rx = (((int)p->px / BLOCK_SIZE) * BLOCK_SIZE) - 0.0001; // rounding the ray's x position to the nearest BLOCK_SIZEth value
		r->ry = (p->px - r->rx) * r->tan_ra + p->py;
		r->x_step = -BLOCK_SIZE;
		r->y_step = -r->x_step * r->tan_ra;
	}
	else if (r->ra < M_PI / 2 || r->ra > 3 * M_PI / 2) // looking right
	{
		r->rx = (((int)p->px / BLOCK_SIZE) * BLOCK_SIZE) + BLOCK_SIZE; // rounding the ray's x position to the nearest BLOCK_SIZEth value
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

t_texture	*get_texture(double ra, bool is_vertical, bool is_left, t_map *map)
{
	if (ra > deg_to_rad(225) && ra < deg_to_rad(315))
	{
		// printf("player facing north\n");
		if (!is_vertical)
			return (&map->n_texture);
		if (is_vertical && is_left)
			return (&map->w_texture);
		if (is_vertical && !is_left)
			return (&map->e_texture);
	}
	else if (ra > deg_to_rad(45) && ra < deg_to_rad(135))
	{
		// printf("player facing south\n");
		if (!is_vertical)
			return (&map->s_texture);
		if (is_vertical && is_left)
			return (&map->e_texture);
		if (is_vertical && !is_left)
			return (&map->w_texture);
	}
	else if (ra > deg_to_rad(135) && ra < deg_to_rad(225))
	{
		// printf("player facing west\n");
		if (is_vertical)
			return (&map->w_texture);
		if (!is_vertical && is_left)
			return (&map->s_texture);
		if (!is_vertical && !is_left)
			return (&map->n_texture);
	}
	// if ((ra > deg_to_rad(0) && ra < deg_to_rad(45)) || (ra > deg_to_rad(315) && ra < deg_to_rad(360)))
	else
	{
		// printf("player facing east\n");
		if (is_vertical)
			return (&map->e_texture);
		if (!is_vertical && is_left)
			return (&map->n_texture);
		if (!is_vertical && !is_left)
			return (&map->s_texture);
	}
	// (void)is_vertical;
	// (void)is_left;
	return (&map->n_texture);
}

static void	draw_ray(t_mlx *m, t_ray *r, int ray_no, bool vertical)
{
	double	line_height;
	double	line_offset;
	double	a_diff;		// angle difference between player angle and ray angle
						// used to fix unwanted fisheye effect
	int		i;
	double	ty_step;
	double	ty;
	double	tx;
	int		*colors;
	int		color;
	t_texture	*t;
	
	if (ray_no == 0)
		t = &m->map->n_texture;
	else
		t = get_texture(r->ra, vertical, (m->rays[ray_no - 1].y > r->ry), m->map);
		// t = get_texture(r->ra, vertical, ((ray_no < WIN_WIDTH / 2)), m->map);
	// 3d ray 
	a_diff = fix_angle(m->p->pa - r->ra);
	r->ray_len = r->ray_len * cos(a_diff);
	line_height = (BLOCK_SIZE * WIN_HEIGHT) / r->ray_len;
	line_offset = WIN_HEIGHT / 2 - line_height / 2;
	dda(m, (t_point){ray_no, 0}, (t_point){ray_no, line_offset}, m->map->ceil_color);
	
	colors = (int *)t->addr;
	ty = 0;
	if (vertical)
		tx = (int)(r->ry * (t->width / BLOCK_SIZE)) % t->width;
	else
		tx = (int)(r->rx * (t->width / BLOCK_SIZE)) % t->width;
	ty_step = (double)t->height / line_height;
	i = line_offset - 1;
	while (++i < line_height + line_offset && i < WIN_HEIGHT)
	{
		color = colors[((int)(ty) * t->width + (int)tx) % (t->width * t->height)];
		if (vertical)
			color = (color & 0xfefefe) >> 1;
		my_mlx_pixel_put(m->img, ray_no, i, color);
		ty += ty_step;
	}

	// draw_vertical_line(m, (t_point){ray_no, line_offset}, line_height + line_offset, &m->map->w_texture);
	dda(m, (t_point){ray_no, line_height + line_offset}, (t_point){ray_no, WIN_HEIGHT}, m->map->floor_color);
	
	// 2d ray for minimap
	m->rays[ray_no].x = r->rx;
	m->rays[ray_no].y = r->ry;
}

void	draw_scene(t_mlx* m)
{
	double		ra; // ray angle
	int			i;
	t_ray		h_ray;
	t_ray		v_ray;

	i = -1;
	ra = fix_angle(m->p->pa - ONEDEG * WIN_WIDTH / 2); // move the ray angle back by 30 degrees
	h_ray.max_dof = m->map->map_height;
	v_ray.max_dof = m->map->map_width;
	while (++i < WIN_WIDTH)
	{
		h_ray.ra = ra;
		v_ray.ra = ra;
		check_horizontal_intersect(m->p, &h_ray);
		cast_ray(m->map, &h_ray);
		h_ray.ray_len = get_ray_len(m->p->px, m->p->py, h_ray.rx, h_ray.ry);
		check_vertical_intersect(m->p, &v_ray);
		cast_ray(m->map, &v_ray);
		v_ray.ray_len = get_ray_len(m->p->px, m->p->py, v_ray.rx, v_ray.ry);
		if (h_ray.ray_len <= v_ray.ray_len) // ray hit a horizontal wall
			draw_ray(m, &h_ray, i, false);
		else // ray hit a vertical wall
			draw_ray(m, &v_ray, i, true);
		ra = fix_angle(ra + ONEDEG);
	}
}
