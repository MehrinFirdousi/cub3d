/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 20:49:04 by mfirdous          #+#    #+#             */
/*   Updated: 2023/04/30 13:42:28 by mfirdous         ###   ########.fr       */
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
		m->pos->pa -= 0.1;
		if (m->pos->pa < 0)
			m->pos->pa += 2 * M_PI;
		m->pos->pdx = cos(m->pos->pa) * 5;
		m->pos->pdy = sin(m->pos->pa) * 5;
	}
	if (keycode == RIGHT)
	{
		m->pos->pa += 0.1;
		if (m->pos->pa > 2 * M_PI)
			m->pos->pa -= 2 * M_PI;
		m->pos->pdx = cos(m->pos->pa) * 5;
		m->pos->pdy = sin(m->pos->pa) * 5;
	}
	if (keycode == S)
	{
		ft_printf("S clicked\n");
		m->pos->y_offset -= m->pos->pdy;
		m->pos->x_offset -= m->pos->pdx;
	}
	else if (keycode == W)
	{
		ft_printf("W clicked\n");
		m->pos->y_offset += m->pos->pdy;
		m->pos->x_offset += m->pos->pdx;
	}
	else if (keycode == A)
	{
		ft_printf("A clicked\n");
		m->pos->x_offset -= SPEED;
	}
	else if (keycode == D)
	{
		ft_printf("D clicked\n");
		m->pos->x_offset += SPEED;
	}
	
	redraw_image(m);
	return (0);
}
