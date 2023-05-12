/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:41:38 by mfirdous          #+#    #+#             */
/*   Updated: 2023/05/12 15:46:18 by mfirdous         ###   ########.fr       */
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

int		mouse_move(int x, int y, t_mlx *m)
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
	else if (x > 0 && x < WIN_WIDTH && y > 0 && y < WIN_HEIGHT)
	{
		if (x > ox + 2)
		{
			m->p->pa = fix_angle(m->p->pa + MOUSE_SENS * m->keys->speed);
			m->p->pdx = cos(m->p->pa) * m->keys->speed;
			m->p->pdy = sin(m->p->pa) * m->keys->speed;
		}
		if (x < ox - 2)
		{
			m->p->pa = fix_angle(m->p->pa - MOUSE_SENS * m->keys->speed);
			m->p->pdx = cos(m->p->pa) * m->keys->speed;
			m->p->pdy = sin(m->p->pa) * m->keys->speed;
		}
	}
	if (m->frame_count >= REFRESH_RATE)
	{
		m->map->t_frame = (m->map->t_frame + 1) % FRAME_TOTAL;
		m->frame_count = 0;
	}
	m->frame_count += 150;
	redraw_image(m);
	ox = x;
	oy = y;
	return (0);
}