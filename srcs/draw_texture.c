/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 21:15:52 by mfirdous          #+#    #+#             */
/*   Updated: 2023/05/14 20:32:57 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_texture	*get_wall_texture(t_mlx *m, t_ray *r, t_point p)
{
	bool	x_dec;
	bool	y_dec;

	x_dec = (m->rays[(int)p.x - 1].x > r->rx);
	y_dec = (m->rays[(int)p.x - 1].y > r->ry);
	if (!r->vertical && r->ra > NW && r->ra < NE)
		return (&m->map->n_texture);
	if (!r->vertical && r->ra > SE && r->ra < SW)
		return (&m->map->s_texture);
	if (r->vertical && y_dec)
		return (&m->map->w_texture);
	if (r->vertical && !y_dec)
		return (&m->map->e_texture);
	if (r->vertical && r->ra > SW && r->ra < NW)
		return (&m->map->w_texture);
	if (r->vertical)
		return (&m->map->e_texture);
	if (!r->vertical && x_dec)
		return (&m->map->s_texture);
	if (!r->vertical && !x_dec)
		return (&m->map->n_texture);
	return (&m->map->n_texture);
}

void	draw_vertical_line(t_texture *t, t_mlx *m, t_ray *r, t_point p)
{
	double		ty_step;
	int			*colors;
	int			color;
	int			i;

	i = p.y - 1;
	colors = (int *)t->addr;
	t->ty = 0;
	if (r->vertical)
		t->tx = (int)(r->ry * (t->width >> SHIFT_VALUE)) % t->width;
	else
		t->tx = (int)(r->rx * (t->width >> SHIFT_VALUE)) % t->width;
	ty_step = (double)t->height / r->line_height;
	while (++i < r->line_height + p.y && i < WIN_HEIGHT)
	{
		color = colors[abs(((int)(t->ty) * t->width + (int)t->tx)
				% (t->width * t->height))];
		if (r->vertical)
			color = (color & 0xfefefe) >> 1;
		my_mlx_pixel_put(m->img, p.x, i, color);
		t->ty += ty_step;
	}
}

// draws a textured vertical line along the t_point given
void	draw_texture(t_mlx *m, t_ray *r, t_point p)
{
	t_texture	*t;
	int			i;
	int			color;

	if (r->door_status == 1)
		t = &m->map->c_door_texture;
	else if ((r->door_status == 2 && r->vertical)
		|| (r->door_status == 3 && !r->vertical))
		t = &m->map->o_door_texture;
	else
		t = get_wall_texture(m, r, p);
	if (t->img)
		draw_vertical_line(t, m, r, p);
	else
	{
		i = p.y - 1;
		if (r->vertical)
			color = TEAL_D;
		else
			color = TEAL;
		while (++i < r->line_height + p.y && i < WIN_HEIGHT)
			my_mlx_pixel_put(m->img, p.x, i, color);
	}
}
