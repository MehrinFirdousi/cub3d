/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 20:49:04 by mfirdous          #+#    #+#             */
/*   Updated: 2023/05/01 22:02:40 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_hold_keys(int keycode, t_keys *keys, bool status)
{
	if (keycode == LEFT)
		keys->left = status;
	if (keycode == RIGHT)
		keys->right = status;
	if (keycode == UP)
		keys->up = status;
	if (keycode == DOWN)
		keys->down = status;
	if (keycode == S)
		keys->s = status;
	if (keycode == W)
		keys->w = status;
	if (keycode == A)
		keys->a = status;
	if (keycode == D)
		keys->d = status;
}

int	key_up_handler(int keycode, t_mlx *m)
{
	set_hold_keys(keycode, m->keys, false);
	if (keycode == ESC)
	{
		mlx_destroy_window(m->mlx, m->win);
		exit_free(m);
	}
	if (keycode == SHIFT)
	{
		m->keys->shift = false;
		m->keys->speed = 1;
		m->p->pdx = cos(m->p->pa) * STRAFE_SPEED;
		m->p->pdy = sin(m->p->pa) * STRAFE_SPEED;
	}
	if (keycode == TAB)
	{
		m->keys->tab = !m->keys->tab;
		redraw_image(m);
	}
	if (keycode == E)
		open_door(m);
	if (keycode == Q)
		toggle_mouse(m);
	return (0);
}

int	key_down_handler(int keycode, t_mlx *m)
{
	set_hold_keys(keycode, m->keys, true);
	if (keycode == SHIFT)
	{
		m->keys->shift = true;
		m->keys->speed = 0.5;
		m->p->pdx = cos(m->p->pa) * STRAFE_SPEED * m->keys->speed;
		m->p->pdy = sin(m->p->pa) * STRAFE_SPEED * m->keys->speed;
	}
	return (0);
}

int	key_hold_handler(t_mlx *m)
{
	change_player_direction(m);
	move_player(m);
	if (m->frame_count >= REFRESH_RATE)
	{
		m->map->t_frame = (m->map->t_frame + 1) % FRAME_TOTAL;
		redraw_image(m);
		m->frame_count = 0;
	}
	if (m->keys->left | m->keys->right | m->keys->s | m->keys->w | m->keys->a
		| m->keys->d | m->keys->shift | m->keys->up | m->keys->down)
	{
		m->frame_count += 200;
		redraw_image(m);
	}
	m->frame_count++;
	return (0);
}
