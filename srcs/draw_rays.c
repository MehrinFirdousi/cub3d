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

// static void	draw_ray(t_mlx *m, t_ray *r, int ray_no, int color)
// {
// 	double	line_height;
// 	double	line_offset;
// 	double	a_diff;		// angle difference between player angle and ray angle
// 						// used to fix unwanted fisheye effect

// 	// 3d ray 
// 	a_diff = fix_angle(m->p->pa - r->ra);
// 	r->ray_len = r->ray_len * cos(a_diff);
// 	line_height = (BLOCK_SIZE * WIN_HEIGHT) / r->ray_len;
// 	line_offset = WIN_HEIGHT / 2 - line_height / 2;
// 	// dda(m, (t_point){ray_no, line_offset}, (t_point){ray_no, line_height + line_offset}, ray_no, line_offset, ray_no, line_height + line_offset, color);
// 	dda(m, (t_point){ray_no, 0}, (t_point){ray_no, line_offset}, m->map->ceil_color);
// 	dda(m, (t_point){ray_no, line_offset}, (t_point){ray_no, line_height + line_offset}, color);
// 	dda(m, (t_point){ray_no, line_height + line_offset}, (t_point){ray_no, WIN_HEIGHT}, m->map->floor_color);
	
// 	// 2d ray for minimap
// 	m->rays[ray_no].x = r->rx;
// 	m->rays[ray_no].y = r->ry;
// 	// dda(m, (t_point){m->p->px, m->p->py}, (t_point){r->rx, r->ry}, color);
// }

static void	draw_vertical_line(t_mlx *m, t_point p, int y_end, t_texture *texture)
{
	int	y;
	int	i;
	int	j;
	int	*colors;
	int	repeat_rate;

	colors = (int *)texture->addr;
	i = -1;
	y = p.y - 1;
	repeat_rate = (y_end - p.y) / texture->height;
	while (++y < y_end && y < WIN_HEIGHT && ++i < texture->height)
	{
		j = -1;
		my_mlx_pixel_put(m->img, p.x, y, colors[i * texture->width]);
		// while (++j < repeat_rate)
			// my_mlx_pixel_put(m->img, p.x, ++y, colors[i * texture->width]);
	}
}

static void	draw_ray(t_mlx *m, t_ray *r, int ray_no, int color)
{
	double	line_height;
	double	line_offset;
	double	a_diff;		// angle difference between player angle and ray angle
						// used to fix unwanted fisheye effect
	int		i;
	// 3d ray 
	a_diff = fix_angle(m->p->pa - r->ra);
	r->ray_len = r->ray_len * cos(a_diff);
	line_height = (BLOCK_SIZE * WIN_HEIGHT) / r->ray_len;
	line_offset = WIN_HEIGHT / 2 - line_height / 2;
	i = line_offset - 1;
	dda(m, (t_point){ray_no, 0}, (t_point){ray_no, line_offset}, m->map->ceil_color);	
	// while (++i < line_height + line_offset && i < WIN_HEIGHT)
	// {
	// 	my_mlx_pixel_put(m->img, ray_no, i, color);
	// }
	draw_vertical_line(m, (t_point){ray_no, line_offset}, line_height + line_offset, &m->map->s_texture);
	dda(m, (t_point){ray_no, line_height + line_offset}, (t_point){ray_no, WIN_HEIGHT}, m->map->floor_color);
	
	(void)color;
	// 2d ray for minimap
	m->rays[ray_no].x = r->rx;
	m->rays[ray_no].y = r->ry;
}

void	draw_scene(t_mlx* m)
{
	double	ra; // ray angle
	int		i;
	t_ray	h_ray;
	t_ray	v_ray;
	
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
			draw_ray(m, &h_ray, i, TEAL);
		else // ray hit a vertical wall
			draw_ray(m, &v_ray, i, TEAL_D);
		ra = fix_angle(ra + ONEDEG); 
	}
}
