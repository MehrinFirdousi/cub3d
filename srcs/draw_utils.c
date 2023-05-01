/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 01:49:53 by mfirdous          #+#    #+#             */
/*   Updated: 2023/05/02 01:49:53 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

// void	dda(t_mlx *m, int x1, int y1, int x2, int y2, int color)
// {
// 	int			i;
// 	float		x;
// 	float		y;
// 	t_dda_dat	d;

// 	d.dx = x2 - x1;
// 	d.dy = y2 - y1;
// 	d.dx_abs = abs(d.dx);
// 	d.dy_abs = abs(d.dy);
// 	if (d.dx_abs > d.dy_abs)
// 		d.steps = d.dx_abs;
// 	else
// 		d.steps = d.dy_abs;
// 	d.x_inc = d.dx / (float)d.steps;
// 	d.y_inc = d.dy / (float)d.steps;
// 	x = x1;
// 	y = y1;
// 	i = -1;
// 	while (++i <= d.steps)
// 	{
// 		my_mlx_pixel_put(m->img, x, y, color);
// 		x += d.x_inc;
// 		y += d.y_inc;
// 	}
// }

void	dda(t_mlx *m, t_point p1, t_point p2, int color)
{
	int			i;
	float		x;
	float		y;
	t_dda_dat	d;

	d.dx = p2.x - p1.x;
	d.dy = p2.y - p1.y;
	d.dx_abs = abs(d.dx);
	d.dy_abs = abs(d.dy);
	if (d.dx_abs > d.dy_abs)
		d.steps = d.dx_abs;
	else
		d.steps = d.dy_abs;
	d.x_inc = d.dx / (float)d.steps;
	d.y_inc = d.dy / (float)d.steps;
	x = p1.x;
	y = p1.y;
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