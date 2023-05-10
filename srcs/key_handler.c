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

int	exit_free(t_mlx *m)
{
	mlx_destroy_image(m->mlx, m->img->img);
	// mlx_destroy_image(m->mlx, m->map->n_texture.img);
	// mlx_destroy_image(m->mlx, m->map->s_texture.img);
	// mlx_destroy_image(m->mlx, m->map->w_texture.img);
	// mlx_destroy_image(m->mlx, m->map->e_texture.img);
	// mlx_destroy_image(m->mlx, m->map->c_door_texture.img);
	free(m->map->n_texture.path);
	free(m->map->s_texture.path);
	free(m->map->w_texture.path);
	free(m->map->e_texture.path);
	free(m->rays);
	ft_split_destroy(m->map->map);
	exit(0);
}

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
	mlx_put_image_to_window(m->mlx, m->win, m->map->torch[m->map->torch_frame].img, WIN_WIDTH * 0.7, WIN_HEIGHT * 0.45);
}

bool	open_door(t_mlx *m)
{
	int	r_mapx;
	int	r_mapy;

	r_mapx = (int)m->rays[WIN_WIDTH / 2].x / BLOCK_SIZE;
	r_mapy = (int)m->rays[WIN_WIDTH / 2].y / BLOCK_SIZE;
	if (r_mapx >= 0 && r_mapy >= 0 && r_mapx < m->map->map_width && r_mapy < m->map->map_height)
	{
		printf("e cliwked\n");
		if (m->map->map[r_mapy][r_mapx] == 'D')
			m->map->map[r_mapy][r_mapx] = 'O';
		if (m->map->map[r_mapy][r_mapx] == '1')
		{
			if (r_mapx > 0 && r_mapy > 0 && r_mapx < m->map->map_width - 1 && r_mapy < m->map->map_height - 1)
			{
				if (m->map->map[r_mapy][r_mapx + 1] == 'O')
					m->map->map[r_mapy][r_mapx + 1] = 'D';
				if (m->map->map[r_mapy][r_mapx - 1] == 'O')
					m->map->map[r_mapy][r_mapx - 1] = 'D';
				if (m->map->map[r_mapy + 1][r_mapx] == 'O')
					m->map->map[r_mapy + 1][r_mapx] = 'D';
				if (m->map->map[r_mapy - 1][r_mapx] == 'O')
					m->map->map[r_mapy - 1][r_mapx] = 'D';
			}
		}
		return (true);
	}
	return (false);
}

int	key_up_handler(int keycode, t_mlx *m)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(m->mlx, m->win);
		exit_free(m);
	}
	if (keycode == LEFT)
		m->keys->left = false;
	if (keycode == RIGHT)
		m->keys->right = false;
	if (keycode == S)
		m->keys->s = false;
	if (keycode == W)
		m->keys->w = false;
	if (keycode == A)
		m->keys->a = false;
	if (keycode == D)
		m->keys->d = false;
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
		if (open_door(m))
			redraw_image(m);
	return (0);
}

int	key_down_handler(int keycode, t_mlx *m)
{
	if (keycode == LEFT)
		m->keys->left = true;
	if (keycode == RIGHT)
		m->keys->right = true;
	if (keycode == S)
		m->keys->s = true;
	if (keycode == W)
		m->keys->w = true;
	if (keycode == A)
		m->keys->a = true;
	if (keycode == D)
		m->keys->d = true;
	if (keycode == Q)
	{
		if(m->map->q_flag)
		{
			mlx_mouse_show();
			m->map->q_flag = !m->map->q_flag;	
		}
		else if(!m->map->q_flag)
		{
			mlx_mouse_hide();
			m->map->q_flag = !m->map->q_flag;
		}
		m->keys->q = true;
	}
	if (keycode == SHIFT)
	{
		m->keys->shift = true;
		m->keys->speed = 0.5;
		m->p->pdx = cos(m->p->pa) * STRAFE_SPEED * m->keys->speed;
		m->p->pdy = sin(m->p->pa) * STRAFE_SPEED * m->keys->speed;
	}
	return (0);
}

bool	player_hit_wall(double px, double py, t_map *map)
{
	int	p_mapx;
	int	p_mapy;

	p_mapx = (int)px / BLOCK_SIZE;
	p_mapy = (int)py / BLOCK_SIZE;
	if (p_mapx >= 0 && p_mapy >= 0 && p_mapx < map->map_width && p_mapy < map->map_height)
		if (map->map[p_mapy][p_mapx] == '1' || map->map[p_mapy][p_mapx] == 'D') // if we hit a wall
			return (true);
	return (false);
}

int	mouse_move(int x, int y, t_mlx *m)
{
	static int	ox;
	static int	mouse_left;
	static int	mouse_right;

	if (m->keys->s)
	{
		if (player_hit_wall(m->p->px - 3 * m->p->pdx, m->p->py - 3 * m->p->pdy, m->map))
			return (0);
		m->p->px -= m->p->pdx;
		m->p->py -= m->p->pdy;
	}
	if (m->keys->w)
	{
		if (player_hit_wall(m->p->px + 3 * m->p->pdx, m->p->py + 3 * m->p->pdy, m->map))
			return (0);
		m->p->px += m->p->pdx;
		m->p->py += m->p->pdy;
	}
	if (m->keys->a)
	{
		if (player_hit_wall(m->p->px + 3 * m->p->pdy, m->p->py - 3 * m->p->pdx, m->map))
			return (0);
		m->p->px += m->p->pdy;
		m->p->py -= m->p->pdx;
	}
	if (m->keys->d)
	{
		if (player_hit_wall(m->p->px - 3 * m->p->pdy, m->p->py + 3 * m->p->pdx, m->map))
			return (0);
		m->p->px -= m->p->pdy;
		m->p->py += m->p->pdx;
	}
	if(m->map->q_flag)
	{
		if((x < 0 || x > WIN_WIDTH) || y < 0 || y > WIN_HEIGHT)
				mlx_mouse_move(m->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
		else if(x > 0 && x < WIN_WIDTH && y > 0 && y < WIN_HEIGHT)
		{
			// printf("inside x == %d\n", x);
			if (x > ox)
			{
				mouse_right = 1;
				m->p->pa += (0.03 * m->keys->speed);
				m->p->pdx = cos(m->p->pa) * 1 * m->keys->speed;
				m->p->pdy = sin(m->p->pa) * 1 * m->keys->speed;
			}
			if (x < ox)
			{
				mouse_left = 1;
				m->p->pa -= (0.03 * m->keys->speed);
				m->p->pdx = cos(m->p->pa) * 1 * m->keys->speed;
				m->p->pdy = sin(m->p->pa) * 1 * m->keys->speed;
			}
		}
	}
	ox = x;
	if (m->frame_count >= FPS)
	{
		m->map->torch_frame = (m->map->torch_frame + 1) % FRAME_TOTAL;
		m->frame_count = 0;
	}
	if (mouse_right | mouse_left | \
		m->keys->s | m->keys->w | m->keys->a | m->keys->d)
	{
		m->frame_count+=150;
		redraw_image(m);
	}
	return (0);
}

// void	refresh()
int	key_hold_handler(t_mlx *m)
{
	// static	int	frame_count;

	if (m->keys->left)
	{
		m->p->pa -= (TURN_SPEED * m->keys->speed);
		if (m->p->pa < 0)
			m->p->pa += TWO_PI;
		m->p->pdx = cos(m->p->pa) * STRAFE_SPEED * m->keys->speed;
		m->p->pdy = sin(m->p->pa) * STRAFE_SPEED * m->keys->speed;
	}
	if (m->keys->right)
	{
		m->p->pa += (TURN_SPEED * m->keys->speed);
		if (m->p->pa > TWO_PI)
			m->p->pa -= TWO_PI;
		m->p->pdx = cos(m->p->pa) * STRAFE_SPEED * m->keys->speed;
		m->p->pdy = sin(m->p->pa) * STRAFE_SPEED * m->keys->speed;
	}
	if (m->keys->s)
	{
		if (player_hit_wall(m->p->px - 3 * m->p->pdx, m->p->py - 3 * m->p->pdy, m->map))
			return (0);
		m->p->px -= m->p->pdx;
		m->p->py -= m->p->pdy;
	}
	if (m->keys->w)
	{
		if (player_hit_wall(m->p->px + 3 * m->p->pdx, m->p->py + 3 * m->p->pdy, m->map))
			return (0);
		m->p->px += m->p->pdx;
		m->p->py += m->p->pdy;
	}
	if (m->keys->a)
	{
		if (player_hit_wall(m->p->px + 3 * m->p->pdy, m->p->py - 3 * m->p->pdx, m->map))
			return (0);
		m->p->px += m->p->pdy;
		m->p->py -= m->p->pdx;
	}
	if (m->keys->d)
	{
		if (player_hit_wall(m->p->px - 3 * m->p->pdy, m->p->py + 3 * m->p->pdx, m->map))
			return (0);
		m->p->px -= m->p->pdy;
		m->p->py += m->p->pdx;
	}
	// if (frame_count >= FPS)
	if (m->frame_count >= FPS)
	{
		m->map->torch_frame = (m->map->torch_frame + 1) % FRAME_TOTAL;
		redraw_image(m);
		// frame_count = 0;
		m->frame_count = 0;
	}
	// printf("fps %d\n", frame_count);
	// frame_count++;
	m->frame_count++;
	if (m->keys->left | m->keys->right | \
		m->keys->s | m->keys->w | m->keys->a | m->keys->d | m->keys->shift)
	{
		// frame_count += 200;
		m->frame_count += 200;
		redraw_image(m);
	}
	return (0);
}
