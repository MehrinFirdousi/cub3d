/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redraw_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:58:02 by mfirdous          #+#    #+#             */
/*   Updated: 2023/05/12 15:58:31 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	redraw_image(t_mlx *m)
{
	mlx_destroy_image(m->mlx, m->img->img);
	m->img->img = mlx_new_image(m->mlx, WIN_WIDTH, WIN_HEIGHT);
	m->img->addr = mlx_get_data_addr(m->img->img, &(m->img->bits_per_pixel), \
							&(m->img->line_length), &(m->img->endian));
	m->img->bits_per_pixel >>= 3;
	draw_scene(m);
	if (m->keys->tab)
		draw_minimap(m);
	mlx_put_image_to_window(m->mlx, m->win, m->img->img, 0, 0);
	if (m->map->torch[m->map->t_frame].img)
		mlx_put_image_to_window(m->mlx, m->win,
			m->map->torch[m->map->t_frame].img,
			WIN_WIDTH * 0.7, WIN_HEIGHT * 0.45);
}
