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
}

bool	open_door(t_mlx *m)
{
	int	r_mapx;
	int	r_mapy;

	r_mapx = (int)m->rays[WIN_WIDTH / 2].x / BLOCK_SIZE;
	r_mapy = (int)m->rays[WIN_WIDTH / 2].y / BLOCK_SIZE;
	if (r_mapx >= 0 && r_mapy >= 0 && r_mapx < m->map->map_width && r_mapy < m->map->map_height)
	{
		if (m->map->map[r_mapy][r_mapx] == 'D')
			m->map->map[r_mapy][r_mapx] = 'O';
		// else if (m->map->map[r_mapy][r_mapx] == 'O')
		// {
		// 	m->map->map[r_mapy][r_mapx] = '1';
		// 	if (m->map->map[r_mapy + 1][r_mapx] == '')
		// }
			m->map->map[r_mapy][r_mapx] = 'D';
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
	// printf("keycode = %d\n", keycode);
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
	if (p_mapx >= 0 && p_mapy >= 0 && p_mapx < map->map_width && p_mapy < map->map_height \
		&& map->map[p_mapy][p_mapx] == '1') // if we hit a wall
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
		// printf("before %lf %lf\n", m->p->px, m->p->py);
		// player_hit_wall2(m->p, m->map);
		// printf("after %lf %lf\n", m->p->px, m->p->py);
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
	if((x < 0 || x > WIN_WIDTH) || y < 0 || y > WIN_HEIGHT)
		mlx_mouse_move(m->win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	if(x > 0 && x < WIN_WIDTH && y > 0 && y < WIN_HEIGHT)
	{
		printf("inside x == %d\n", x);
		mlx_mouse_hide();
		if (x > ox)
		{
			mouse_right = 1;
			m->p->pa += (0.07 * m->keys->speed);
			m->p->pdx = cos(m->p->pa) * 1 * m->keys->speed;
			m->p->pdy = sin(m->p->pa) * 1 * m->keys->speed;
		}
		if (x < ox)
		{
			mouse_left = 1;
			m->p->pa -= (0.07 * m->keys->speed);
			m->p->pdx = cos(m->p->pa) * 1 * m->keys->speed;
			m->p->pdy = sin(m->p->pa) * 1 * m->keys->speed;
		}
	}
	ox = x;
	if (mouse_right | mouse_left | \
		m->keys->s | m->keys->w | m->keys->a | m->keys->d)
		redraw_image(m);
	return (0);
}

// void	player_hit_wall2(t_player *p, t_map *map)
// {
// 	int	px_cur; // player's x position in the map
// 	int	py_cur; // player's y position in the map
// 	int	x_offset;
// 	int	y_offset;
// 	int	px_next;
// 	int	py_next;

// 	px_cur = p->px / BLOCK_SIZE;
// 	py_cur = p->py / BLOCK_SIZE;
// 	x_offset = 20;
// 	y_offset = 20;
// 	if (px_cur < 0)
// 		x_offset = -20;
// 	if (py_cur < 0)
// 		y_offset = -20;
// 	px_next = (p->px + x_offset) / BLOCK_SIZE;
// 	py_next = (p->py + y_offset) / BLOCK_SIZE;
// 	if (px_cur >= 0 && py_cur >= 0 && px_cur < map->map_width && py_cur < map->map_height)
// 	{
// 		printf("%d, %d\n%d, %d\n", py_cur, px_next, py_next, px_cur);
// 		if (map->map[py_cur][px_next] == '0')
// 		{
// 			printf("hello1\n");
// 			p->px += p->pdx;
// 		}
// 		if (map->map[py_next][px_cur] == '0')
// 		{
// 			printf("hello2\n");
// 			p->py += p->pdy;
// 		}
// 	}

// }

int	key_hold_handler(t_mlx *m)
{
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
		// printf("before %lf %lf\n", m->p->px, m->p->py);
		// player_hit_wall2(m->p, m->map);
		// printf("after %lf %lf\n", m->p->px, m->p->py);
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
	if (m->keys->left | m->keys->right | \
		m->keys->s | m->keys->w | m->keys->a | m->keys->d | m->keys->shift)
		redraw_image(m);
	return (0);
}
