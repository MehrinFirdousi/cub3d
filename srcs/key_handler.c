/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 20:49:04 by mfirdous          #+#    #+#             */
/*   Updated: 2023/04/29 18:47:52 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_click_handler(int keycode, t_mlx *m)
{
	if (keycode == ESC)
	{
		mlx_destroy_image(m->mlx, m->img->img);
		mlx_destroy_window(m->mlx, m->win);
		exit(0);
	}
	if (keycode == S)
	{
		ft_printf("S clicked\n");
		m->y_offset += 5;
	}
		
	else if (keycode == W)
	{
		ft_printf("W clicked\n");
		m->y_offset -= 5;
	}
	else if (keycode == A)
	{
		ft_printf(" clicked\n");
		m->x_offset -= 5;
	}
	else if (keycode == D)
		m->x_offset += 5;
	draw_blocks_2d(m);
	return (0);
}
