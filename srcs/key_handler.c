/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 20:49:04 by mfirdous          #+#    #+#             */
/*   Updated: 2023/04/27 20:49:37 by mfirdous         ###   ########.fr       */
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
	return (0);
}
