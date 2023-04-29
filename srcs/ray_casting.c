/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 18:00:59 by mfirdous          #+#    #+#             */
/*   Updated: 2023/04/29 18:45:54 by mfirdous         ###   ########.fr       */
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

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
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

void draw_blocks_2d(t_mlx *mlx)
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
			else if (map[i][j] == 2)
			{
				my_mlx_pixel_put(mlx->img, x + size/2 - 1 + mlx->x_offset, y + size/2 - 1 + mlx->y_offset, GREEN); // 0,255,0,0
				my_mlx_pixel_put(mlx->img, x + size/2 + 1 + mlx->x_offset, y + size/2 + 1 + mlx->y_offset, GREEN); // 0,255,0,0
				my_mlx_pixel_put(mlx->img, x + size/2 - 1 + mlx->x_offset, y + size/2 + 1 + mlx->y_offset, GREEN); // 0,255,0,0
				my_mlx_pixel_put(mlx->img, x + size/2 + 1 + mlx->x_offset, y + size/2 - 1 + mlx->y_offset, GREEN); // 0,255,0,0
				// color = GREEN;
			}
			dda(mlx, x + gap, y + gap, \
					 x + gap, y + size - gap,
					 color);
			dda(mlx, x + gap, y + size - gap, \
					 x + size - gap, y + size - gap,
					 color);
			dda(mlx, x + size - gap, y + size - gap, \
					 x + size - gap, y + gap,
					 color);
			dda(mlx, x + size - gap, y + gap, \
					 x + gap, y + gap,
					 color);
			color = GRAY;
		}
	}
}