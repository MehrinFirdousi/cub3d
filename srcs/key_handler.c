/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 20:49:04 by mfirdous          #+#    #+#             */
/*   Updated: 2023/04/30 17:13:40 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	redraw_image(t_mlx *m)
{
	mlx_destroy_image(m->mlx, m->img->img);
	m->img->img = mlx_new_image(m->mlx, WIN_WIDTH, WIN_HEIGHT);
	m->img->addr = mlx_get_data_addr(m->img->img, &(m->img->bits_per_pixel), \
									&(m->img->line_length), &(m->img->endian));
	draw_blocks_2d(m);
	draw_rays_2d(m);
	mlx_put_image_to_window(m->mlx, m->win, m->img->img, 0, 0);
}

int	key_click_handler(int keycode, t_mlx *m)
{
	if (keycode == ESC)
	{
		mlx_destroy_image(m->mlx, m->img->img);
		mlx_destroy_window(m->mlx, m->win);
		exit(0);
	}
	return (0);
}

int	key_hold_handler(int keycode, t_mlx *m)
{
	if (keycode == LEFT)
	{
		m->pos->pa -= TURN_SPEED;
		if (m->pos->pa < 0)
			m->pos->pa += 2 * M_PI;
		m->pos->pdx = cos(m->pos->pa) * 5;
		m->pos->pdy = sin(m->pos->pa) * 5;
	}
	if (keycode == RIGHT)
	{
		m->pos->pa += TURN_SPEED;
		if (m->pos->pa > 2 * M_PI)
			m->pos->pa -= 2 * M_PI;
		m->pos->pdx = cos(m->pos->pa) * 5;
		m->pos->pdy = sin(m->pos->pa) * 5;
	}
	if (keycode == S)
	{
		m->pos->px -= m->pos->pdx;
		m->pos->py -= m->pos->pdy;
		printf("S clicked, dx = %lf, dy = %lf\n", m->pos->pdx, m->pos->pdy);
	}
	else if (keycode == W)
	{
		m->pos->px += m->pos->pdx;
		m->pos->py += m->pos->pdy;
		printf("W clicked, dx = %lf, dy = %lf\n", m->pos->pdx, m->pos->pdy);
	}
	else if (keycode == A)
	{
		ft_printf("A clicked\n");
		m->pos->px -= STRAFE_SPEED;
		// m->pos->px -= m->pos->pdx;
		// m->pos->py += m->pos->pdy;
	}
	else if (keycode == D)
	{
		ft_printf("D clicked\n");
		m->pos->px += STRAFE_SPEED;
		// m->pos->px += m->pos->pdx;
		// m->pos->py -= m->pos->pdy;
	}
	
	redraw_image(m);
	return (0);
}
