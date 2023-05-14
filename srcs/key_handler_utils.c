/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handler_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:38:45 by mfirdous          #+#    #+#             */
/*   Updated: 2023/05/14 20:47:18 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	player_hit_wall(t_mlx *m, int x_dir, int y_dir)
{
	int		p_mapx;
	int		p_mapy;
	double	px;
	double	py;

	if (x_dir == y_dir)
	{
		px = m->p->px + (m->p->pdx * 3 * x_dir);
		py = m->p->py + (m->p->pdy * 3 * y_dir);
	}
	else
	{
		px = m->p->px + (m->p->pdy * 3 * x_dir);
		py = m->p->py + (m->p->pdx * 3 * y_dir);
	}
	p_mapx = (int)px >> SHIFT_VALUE;
	p_mapy = (int)py >> SHIFT_VALUE;
	if (is_within_map_boundaries(p_mapx, p_mapy, m->map, 0))
		if (m->map->map[p_mapy][p_mapx] == '1' ||
			m->map->map[p_mapy][p_mapx] == 'D')
			return (true);
	return (false);
}

void	open_door(t_mlx *m)
{
	int	r_mapx;
	int	r_mapy;

	r_mapx = (int)m->rays[WIN_WIDTH >> 1].x >> SHIFT_VALUE;
	r_mapy = (int)m->rays[WIN_WIDTH >> 1].y >> SHIFT_VALUE;
	if (is_within_map_boundaries(r_mapx, r_mapy, m->map, 0))
	{
		if (m->map->map[r_mapy][r_mapx] == 'D')
			m->map->map[r_mapy][r_mapx] = 'O';
		if (m->map->map[r_mapy][r_mapx] == '1')
		{
			if (is_within_map_boundaries(r_mapx, r_mapy, m->map, 1))
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
		redraw_image(m);
	}
}

void	move_player(t_mlx *m)
{
	if (m->keys->s && !player_hit_wall(m, -1, -1))
	{
		m->p->px -= m->p->pdx;
		m->p->py -= m->p->pdy;
	}
	if (m->keys->w && !player_hit_wall(m, 1, 1))
	{
		m->p->px += m->p->pdx;
		m->p->py += m->p->pdy;
	}
	if (m->keys->a && !player_hit_wall(m, 1, -1))
	{
		m->p->px += m->p->pdy;
		m->p->py -= m->p->pdx;
	}
	if (m->keys->d && !player_hit_wall(m, -1, 1))
	{
		m->p->px -= m->p->pdy;
		m->p->py += m->p->pdx;
	}
}

void	change_player_direction(t_mlx *m)
{
	if (m->keys->left)
	{
		m->p->pa = fix_angle(m->p->pa - TURN_SPEED * m->keys->speed);
		m->p->pdx = cos(m->p->pa) * STRAFE_SPEED * m->keys->speed;
		m->p->pdy = sin(m->p->pa) * STRAFE_SPEED * m->keys->speed;
	}
	if (m->keys->right)
	{
		m->p->pa = fix_angle(m->p->pa + TURN_SPEED * m->keys->speed);
		m->p->pdx = cos(m->p->pa) * STRAFE_SPEED * m->keys->speed;
		m->p->pdy = sin(m->p->pa) * STRAFE_SPEED * m->keys->speed;
	}
	if (m->keys->up && m->p->view_offset < WIN_HEIGHT >> 1)
		m->p->view_offset += VIEW_SPEED;
	if (m->keys->down && m->p->view_offset > -(WIN_HEIGHT >> 1))
		m->p->view_offset -= VIEW_SPEED;
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
	if (m->map->torch[m->map->t_frame].img)
		mlx_put_image_to_window(m->mlx, m->win,
			m->map->torch[m->map->t_frame].img,
			WIN_WIDTH * 0.7, WIN_HEIGHT * 0.45);
}
