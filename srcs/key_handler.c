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
	free(m->map->path_north);
	free(m->map->path_south);
	free(m->map->path_west );
	free(m->map->path_east );
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
	draw_scene(m);
	if (m->keys->tab)
	{
		
	}
		draw_minimap(m);
	mlx_put_image_to_window(m->mlx, m->win, m->img->img, 0, 0);
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
	if (keycode == TAB)
	{
		printf("tab clicked %d\n", m->keys->tab);
		m->keys->tab = !m->keys->tab;
	}
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

int	key_hold_handler(t_mlx *m)
{
	if (m->keys->left)
	{
		m->p->pa -= TURN_SPEED;
		if (m->p->pa < 0)
			m->p->pa += 2 * M_PI;		
		m->p->pdx = cos(m->p->pa) * STRAFE_SPEED;
		m->p->pdy = sin(m->p->pa) * STRAFE_SPEED;
	}
	if (m->keys->right)
	{
		m->p->pa += TURN_SPEED;
		if (m->p->pa > 2 * M_PI)
			m->p->pa -= 2 * M_PI;
		m->p->pdx = cos(m->p->pa) * STRAFE_SPEED;
		m->p->pdy = sin(m->p->pa) * STRAFE_SPEED;
	}
	if (m->keys->s)
	{
		// if (player_hit_wall(m->p->px - m->p->pdx, m->p->py - m->p->pdy, m->map))
		// 	return (0);
		m->p->px -= m->p->pdx;
		m->p->py -= m->p->pdy;
	}
	if (m->keys->w)
	{
		// if (player_hit_wall(m->p->px + m->p->pdx, m->p->py + m->p->pdy, m->map))
			// return (0);
		m->p->px += m->p->pdx;
		m->p->py += m->p->pdy;
	}
	if (m->keys->a)
	{
		// if (player_hit_wall(m->p->px + m->p->pdy, m->p->py - m->p->pdx, m->map))
			// return (0);
		m->p->px += m->p->pdy;
		m->p->py -= m->p->pdx;
	}
	if (m->keys->d)
	{
		// if (player_hit_wall(m->p->px - m->p->pdy, m->p->py + m->p->pdx, m->map))
			// return (0);
		m->p->px -= m->p->pdy;
		m->p->py += m->p->pdx;
	}
	if (m->keys->left | m->keys->right | \
		m->keys->s | m->keys->w | m->keys->a | m->keys->d | m->keys->tab)
		redraw_image(m);
	return (0);
}
