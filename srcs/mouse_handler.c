/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:41:38 by mfirdous          #+#    #+#             */
/*   Updated: 2023/05/14 21:31:41 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	toggle_mouse(t_mlx *m)
{
	if (m->keys->q)
		mlx_mouse_show();
	else
		mlx_mouse_hide();
	m->keys->q = !m->keys->q;
}

static void	update_x_pos(t_mlx *m, bool right_pos)
{
	if (right_pos)
		m->p->pa = fix_angle(m->p->pa + MOUSE_SENS * m->keys->speed);
	else
		m->p->pa = fix_angle(m->p->pa - MOUSE_SENS * m->keys->speed);
	m->p->pdx = cos(m->p->pa) * m->keys->speed;
	m->p->pdy = sin(m->p->pa) * m->keys->speed;
}

static void	update_texture_frame(t_mlx *m)
{
	m->map->t_frame = (m->map->t_frame + 1) % FRAME_TOTAL;
	m->frame_count = 0;
}

static void	redraw_updates(t_mlx *m)
{
	if (m->frame_count >= REFRESH_RATE)
		update_texture_frame(m);
	m->frame_count += 150;
	redraw_image(m);
}

int	mouse_move(int x, int y, t_mlx *m)
{
	static int	ox;
	static int	oy;

	move_player(m);
	if (!m->keys->q)
		return (0);
	if (y < oy - 2 && m->p->view_offset < WIN_HEIGHT >> 1)
		m->p->view_offset += VIEW_SPEED;
	if (y > oy + 2 && m->p->view_offset > -(WIN_HEIGHT >> 1))
		m->p->view_offset -= VIEW_SPEED;
	if (x < 0)
		mlx_mouse_move(m->win, WIN_WIDTH - 1, WIN_HEIGHT >> 1);
	if (x > WIN_WIDTH)
		mlx_mouse_move(m->win, 1, WIN_HEIGHT >> 1);
	if (x > 0 && x < WIN_WIDTH && y > 0 && y < WIN_HEIGHT)
	{
		if (x > ox + 2)
			update_x_pos(m, 1);
		if (x < ox - 2)
			update_x_pos(m, 0);
	}
	redraw_updates(m);
	ox = x;
	oy = y;
	return (0);
}
