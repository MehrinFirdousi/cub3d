/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:15:52 by mfirdous          #+#    #+#             */
/*   Updated: 2023/05/08 22:35:30 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_texture	*get_texture(t_mlx *m, t_ray *r, t_point p)
{
	bool	x_dec;
	bool	y_dec;

	x_dec = (m->rays[(int)p.x - 1].x > r->rx);
	y_dec = (m->rays[(int)p.x - 1].y > r->ry);

	if (!r->vertical && r->ra > deg_to_rad(225) && r->ra < deg_to_rad(315))
		return (&m->map->n_texture);
	if (!r->vertical && r->ra > deg_to_rad(45) && r->ra < deg_to_rad(135))
		return (&m->map->s_texture);
	if (r->vertical && y_dec)
		return (&m->map->w_texture);
	if (r->vertical && !y_dec)
		return (&m->map->e_texture);
	if (r->vertical && r->ra > deg_to_rad(135) && r->ra < deg_to_rad(225))
		return (&m->map->w_texture);
	if (r->vertical)
		return (&m->map->e_texture);
	if (!r->vertical && x_dec)
		return (&m->map->s_texture);
	if (!r->vertical && !x_dec)
		return (&m->map->n_texture);
	return (&m->map->n_texture);
}

// draws a textured vertical line along the t_point given
void	draw_texture(t_mlx *m, t_ray *r, t_point p, double l_height)
{
	t_texture	*t;
	int			i;
	double		ty_step;
	int			*colors;
	int			color;

	i = p.y - 1;
	if (r->door_status == 1)
		t = &m->map->c_door_texture;
	else if (r->door_status == 2 && r->vertical)
		t = &m->map->c_door_texture;
	else
		t = get_texture(m, r, p);
	colors = (int *)t->addr;
	t->ty = 0;
	if (r->vertical)
		t->tx = (int)(r->ry * (t->width / BLOCK_SIZE)) % t->width;
	else
		t->tx = (int)(r->rx * (t->width / BLOCK_SIZE)) % t->width;
	ty_step = (double)t->height / l_height;
	while (++i < l_height + p.y && i < WIN_HEIGHT)
	{
		color = colors[abs(((int)(t->ty) * t->width + (int)t->tx)
			% (t->width * t->height))];
		if (r->vertical)
			color = (color & 0xfefefe) >> 1;
		my_mlx_pixel_put(m->img, p.x, i, color);
		t->ty += ty_step;
	}
}
