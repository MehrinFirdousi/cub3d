/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 18:00:59 by mfirdous          #+#    #+#             */
/*   Updated: 2023/04/30 17:04:52 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char map[8][8] = {
				{ 1,1,1,1,1,1,1,1 },
				{ 1,0,1,0,0,0,0,1 },
				{ 1,0,1,0,0,0,0,1 },
				{ 1,0,1,0,0,0,0,1 },
				{ 1,0,0,0,0,0,0,1 },
				{ 1,0,0,0,2,1,0,1 },
				{ 1,0,0,0,0,0,0,1 },
				{ 1,1,1,1,1,1,1,1 }
};

int size = 64;
int gap = 4;

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

void draw_rays_2d(t_mlx* m)
{
	double	ra; // ray angle 
	double	rx;
	double	ry;
	double	x_offset;
	double	y_offset;
	double	a_tan;
	int		dof;
	int		mx;
	int		my;
	int		num_rays;
	int		i;

	i = -1;
	num_rays = 1;
	ra = m->pos->pa;
	while (++i < num_rays)
	{
		dof = 0;
		a_tan = -1 / tan(ra);
		if (ra > M_PI) // looking up
		{
			ry = ((int)m->pos->py >> 6) << 6; // rounding the ray's y position to the nearest 64th value
			rx = (m->pos->py - ry) * a_tan + m->pos->px;
			y_offset = -size;
			x_offset = -y_offset * a_tan;
		}
		else if (ra < M_PI) // looking down
		{
			ry = (((int)m->pos->py >> 6) << 6) + size; // rounding the ray's y position to the nearest 64th value
			rx = (m->pos->py - ry) * a_tan + m->pos->px;
			y_offset = size;
			x_offset = -y_offset * a_tan;
		}
		else if (ra == 0 || ra == M_PI) // ray is exactly facing right or left
		{
			rx = m->pos->px;
			ry = m->pos->py;
			dof = 8;
		}
		while (dof < 8)
		{
			// finding the ray hit position in the map array, divide by size(64)
			mx = (int)rx >> 6;
			my = (int)ry >> 6;
			printf("ray facing (%d, %d)\n", my, mx);
			// mp = my * 8 + mx;
			if (mx >= 0 && my >= 0 && mx < 8 && my < 8 && map[my][mx] == 1) // if we hit a wall
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
		dda(m, m->pos->px, m->pos->py, rx, ry, RED);
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
	while (++i < 8)
	{
		j = -1;
		while (++j < 8)
		{
			x = j * size;
			y = i * size;
			if (map[i][j] == 1)
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
			if (map[i][j] == 2)
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