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

// char map[8][8] = {
// 				{ 1,1,1,1,1,1,1,1 },
// 				{ 1,0,1,0,0,0,0,1 },
// 				{ 1,0,1,0,0,0,0,1 },
// 				{ 1,0,1,0,0,0,0,1 },
// 				{ 1,0,0,0,0,0,0,1 },
// 				{ 1,0,0,0,2,1,0,1 },
// 				{ 1,0,0,0,0,0,0,1 },
// 				{ 1,1,1,1,1,1,1,1 }
// };

int size = BLOCK_SIZE;
int gap = 1;

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && y >= 0 && x < WIN_WIDTH && y < WIN_HEIGHT)
	{
		dst = data->addr + \
				(y * data->line_length + x * (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	dda(t_mlx *m, int x1, int y1, int x2, int y2, int color)
{
	int			i;
	float		x;
	float		y;
	t_dda_dat	d;

	d.dx = x2 - x1;
	d.dy = y2 - y1;
	d.dx_abs = abs(d.dx);
	d.dy_abs = abs(d.dy);
	if (d.dx_abs > d.dy_abs)
		d.steps = d.dx_abs;
	else
		d.steps = d.dy_abs;
	d.x_inc = d.dx / (float)d.steps;
	d.y_inc = d.dy / (float)d.steps;
	x = x1;
	y = y1;
	i = -1;
	while (++i <= d.steps)
	{
		my_mlx_pixel_put(m->img, x, y, color);
		x += d.x_inc;
		y += d.y_inc;
	}
}

double	get_ray_len(double px, double py, double rx, double ry)
{
	return (sqrt(pow(rx - px, 2) + pow(ry - py, 2)));
}

double	fix_angle(double a)
{
	if (a < 0)
		a += 2 * M_PI;
	else if (a > 2 * M_PI)
		a -= 2 * M_PI;
	return (a);
}

void	check_horizontal_intersect(t_pos *p, t_ray *r)
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
		r->dof = 8;
	}
}

void	check_vertical_intersect(t_pos *p, t_ray *r)
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
		r->dof = 8;
	}
}

// casts a ray till it hits a wall
void	cast_ray(t_map *m, t_ray *r)
{
	int	mx;
	int	my;

	while (r->dof < 8)
	{
		// finding the ray hit position in the map array, divide by size(BLOCK_SIZE)
		mx = (int)r->rx / BLOCK_SIZE;
		my = (int)r->ry / BLOCK_SIZE;
		// printf("ray facing (%d, %d)\n", my, mx);
		if (mx >= 0 && my >= 0 && mx < m->map_width && my < m->map_height && m->map[my][mx] == '1') // if we hit a wall
			break;
		else
		{
			r->rx += r->x_step;
			r->ry += r->y_step;
			r->dof++;
		}
	}
}

void	draw_ray(t_mlx *m, t_ray *r, int ray_no, int color)
{
	double	line_height;
	double	line_offset;
	double	a_diff;		// angle difference between player angle and ray angle
						// used to fix unwanted fisheye effect

	// 2d ray for minimap
	dda(m, m->pos->px, m->pos->py, r->rx, r->ry, color);
	
	// 3d ray 
	a_diff = fix_angle(m->pos->pa - r->ra);
	r->ray_len = r->ray_len * cos(a_diff);
	line_height = (BLOCK_SIZE * WIN_HEIGHT) / r->ray_len;
	line_offset = WIN_HEIGHT / 2 - line_height / 2;
	if (ray_no == 0)
		printf("%d ray_len = %lf, line_height = %lf, line_offset = %lf\n", ray_no, r->ray_len, line_height, line_offset);
	dda(m, ray_no, line_offset, ray_no, line_height + line_offset, color);
}

void draw_rays_2d(t_mlx* m)
{
	double	ra; // ray angle
	int		i;
	t_ray	h_ray;
	t_ray	v_ray;
	
	i = -1;
	ra = fix_angle(m->pos->pa - ONEDEG * WIN_WIDTH / 2); // move the ray angle back by 30 degrees 
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
		if (h_ray.ray_len <= v_ray.ray_len) // ray hit a horiontal wall
			draw_ray(m, &h_ray, i, TEAL);
		else // ray hit a vertical wall
			draw_ray(m, &v_ray, i, TEAL_D);
		ra = fix_angle(ra + ONEDEG);
	}
}

void draw_blocks_2d(t_mlx *m)
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
			x = j * size;
			y = i * size;
			if (m->map->map[i][j] == '1')
				color = WHITE;
			dda(m, x + gap, y + gap, \
					x + gap, y + size - gap,
					color);
			dda(m, x + gap, y + size - gap, \
					x + size - gap, y + size - gap,
					color);
			dda(m, x + size - gap, y + size - gap, \
					x + size - gap, y + gap,
					color);
			dda(m, x + size - gap, y + gap, \
					x + gap, y + gap,
					color);
			if (m->map->map[i][j] == 'N')
			{
				color = GREEN;
				my_mlx_pixel_put(m->img, m->pos->px, m->pos->py, color);
				my_mlx_pixel_put(m->img, m->pos->px + 1, m->pos->py, color);
				my_mlx_pixel_put(m->img, m->pos->px + 1, m->pos->py + 1, color);
				my_mlx_pixel_put(m->img, m->pos->px, m->pos->py + 1, color);
				dda(m, m->pos->px, m->pos->py, m->pos->px + (m->pos->pdx * 5), m->pos->py + (m->pos->pdy * 5), color);
			}
			color = GRAY;
		}
	}
}