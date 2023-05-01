/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 18:00:59 by mfirdous          #+#    #+#             */
/*   Updated: 2023/05/01 17:12:38 by mfirdous         ###   ########.fr       */
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

int size = 64;
int gap = 2;

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

void draw_rays_2d(t_mlx* m)
{
	double	ra; // ray angle 
	double	rx;
	double	ry;
	double	hx;
	double	hy;
	double	vx;
	double	vy;
	double	x_offset;
	double	y_offset;
	double	a_tan;
	double	n_tan;
	int		dof;
	int		mx;
	int		my;
	int		num_rays;
	double	len_h;
	double	len_v;
	double	ray_distance;
	double	line_height;
	double	line_offset;
	double	a_diff;
	int		i;
	int		color;

	i = -1;
	num_rays = 60;

	// move the ray angle back by 30 degrees 
	ra = fix_angle(m->pos->pa - ONEDEG * 30);
	// ra = m->pos->pa;
	while (++i < num_rays)
	{
		// Check horizontal intersection
		dof = 0;
		a_tan = -(1 / tan(ra));
		if (ra > M_PI) // looking up
		{
			ry = (((int)m->pos->py / 64) * 64) - 0.0001; // rounding the ray's y position to the nearest 64th value
			rx = (m->pos->py - ry) * a_tan + m->pos->px;
			y_offset = -64;
			x_offset = -y_offset * a_tan;
			printf("player looking up, (xo, yo) = (%lf, %lf)\n", x_offset, y_offset);
		}
		else if (ra < M_PI) // looking down
		{
			ry = (((int)m->pos->py / 64) * 64) + 64; // rounding the ray's y position to the nearest 64th value
			rx = (m->pos->py - ry) * a_tan + m->pos->px;
			y_offset = 64;
			x_offset = -y_offset * a_tan;
			printf("player looking down, (xo, yo) = (%lf, %lf)\n", x_offset, y_offset);
		}
		else // ray is exactly facing right or left
		{
			rx = m->pos->px;
			ry = m->pos->py;
			dof = 8;
			printf("player looking straight left or right\n");
		}
		while (dof < 8)
		{
			// finding the ray hit position in the map array, divide by size(64)
			mx = (int)rx / 64;
			my = (int)ry / 64;
			printf("ray facing (%d, %d)\n", my, mx);
			// mp = my * 8 + mx;
			if (mx >= 0 && my >= 0 && mx < m->map->map_width && my < m->map->map_height && m->map->map[my][mx] == '1') // if we hit a wall
			{
				dof = 8;
				break;
			}
			else
			{
				rx += x_offset;
				ry += y_offset;
				dof += 1;
			}
		}
		hx = rx;
		hy = ry;
		len_h = get_ray_len(m->pos->px, m->pos->py, rx, ry);
		// dda(m, m->pos->px, m->pos->py, rx, ry, RED);

		// Check vertical intersection
		dof = 0;
		n_tan = -tan(ra);
		if (ra > M_PI / 2 && ra < 3 * M_PI / 2) // looking left - >90 and <270
		{
			rx = (((int)m->pos->px / 64) * 64) - 0.0001; // rounding the ray's y position to the nearest 64th value
			ry = (m->pos->px - rx) * n_tan + m->pos->py;
			x_offset = -64;
			y_offset = -x_offset * n_tan;
			printf("player looking left, (xo, yo) = (%lf, %lf)\n", x_offset, y_offset);
		}
		else if (ra < M_PI / 2 || ra > 3 * M_PI / 2) // looking right
		{
			rx = (((int)m->pos->px / 64) * 64) + 64; // rounding the ray's y position to the nearest 64th value
			ry = (m->pos->px - rx) * n_tan + m->pos->py;
			x_offset = 64;
			y_offset = -x_offset * n_tan;
			printf("player looking right, (xo, yo) = (%lf, %lf)\n", x_offset, y_offset);
		}
		else // ray is exactly facing right or left
		{
			rx = m->pos->px;
			ry = m->pos->py;
			dof = 8;
			printf("player looking straight left or right\n");
		}
		while (dof < 8)
		{
			// finding the ray hit position in the map array, divide by size(64)
			mx = (int)rx / 64;
			my = (int)ry / 64;
			printf("ray facing (%d, %d)\n", my, mx);
			if (mx >= 0 && my >= 0 && mx < m->map->map_width && my < m->map->map_height && m->map->map[my][mx] == '1') // if we hit a wall
			{
				dof = 8;
				break;
			}
			else
			{
				rx += x_offset;
				ry += y_offset;
				dof += 1;
			}
		}
		vx = rx;
		vy = ry;
		len_v = get_ray_len(m->pos->px, m->pos->py, rx, ry);
		if (len_h <= len_v) // ray hit a horiontal wall
		{
			ray_distance = len_h;
			color = TEAL;
			dda(m, m->pos->px, m->pos->py, hx, hy, color);
		}
		else // ray hit a vertical wall
		{
			ray_distance = len_v;
			color = TEAL_D;
			dda(m, m->pos->px, m->pos->py, vx, vy, color);
		}
		// DRAWING 3D SCENE
		a_diff = fix_angle(m->pos->pa - ra);
		ray_distance = ray_distance * cos(a_diff); 
		line_height = (64 * WIN_HEIGHT) / ray_distance;
		line_offset = WIN_HEIGHT - line_height / 2;
		dda(m, i * 4 + WIN_WIDTH / 2, line_offset, i * 4 + WIN_WIDTH / 2, line_height, color);
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
				if (m->pos->px == 0)
					m->pos->px = x + size / 2;
				if (m->pos->py == 0)
					m->pos->py = y + size / 2;
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