/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:25:33 by mfirdous          #+#    #+#             */
/*   Updated: 2023/05/15 16:59:36 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	xpm_to_img(t_texture *t, t_mlx *m)
{
	t->img = mlx_xpm_file_to_image(m->mlx, t->path, &t->width, &t->height);
	if (t->img)
		t->addr = mlx_get_data_addr(t->img, &t->bits_per_pixel, &t->line_length,
				&t->endian);
}

void	get_textures_from_xpm(t_mlx *m)
{
	xpm_to_img(&m->map->n_texture, m);
	xpm_to_img(&m->map->s_texture, m);
	xpm_to_img(&m->map->e_texture, m);
	xpm_to_img(&m->map->w_texture, m);
	xpm_to_img(&m->map->c_door_texture, m);
	xpm_to_img(&m->map->o_door_texture, m);
}

void	get_torch_sprite(t_mlx *m)
{
	t_texture	*t;
	int			i;

	t = &m->map->torch[0];
	i = -1;
	while (++i < FRAME_TOTAL)
		t[i].img = mlx_xpm_file_to_image(m->mlx, t[i].path, &t[i].width,
				&t[i].height);
}

void	mlx_set_up(t_mlx *m)
{
	m->mlx = mlx_init();
	m->win = mlx_new_window(m->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	m->img->img = mlx_new_image(m->mlx, WIN_WIDTH, WIN_HEIGHT);
	m->img->addr = mlx_get_data_addr(m->img->img, &m->img->bits_per_pixel,
			&m->img->line_length, &m->img->endian);
	m->img->bits_per_pixel >>= 3;
	ft_bzero(m->keys, sizeof(t_keys));
	m->keys->tab = true;
	m->keys->speed = 1;
	m->p->px = (m->p->px * MM_SIZE) + (MM_SIZE / 2);
	m->p->py = (m->p->py * MM_SIZE) + (MM_SIZE / 2);
	m->p->pdx = cos(m->p->pa) * STRAFE_SPEED * m->keys->speed;
	m->p->pdy = sin(m->p->pa) * STRAFE_SPEED * m->keys->speed;
	m->p->view_offset = 0;
	m->rays = ft_malloc(WIN_WIDTH * sizeof(t_point));
	get_textures_from_xpm(m);
	get_torch_sprite(m);
	m->map->t_frame = 0;
	m->frame_count = 0;
}

int	main(int argc, char **argv)
{
	t_mlx		mlx;
	t_img		img;
	t_player	p;
	t_map		map;
	t_keys		keys;

	init_data(&map);
	parsing(argc, argv, &map, &p);
	mlx.img = &img;
	mlx.p = &p;
	mlx.map = &map;
	mlx.keys = &keys;
	mlx_set_up(&mlx);
	draw_scene(&mlx);
	draw_minimap(&mlx);
	mlx_key_hook(mlx.win, key_up_handler, &mlx);
	mlx_hook(mlx.win, 2, 1L << 0, key_down_handler, &mlx);
	mlx_hook(mlx.win, 17, 0, exit_free, &mlx);
	mlx_hook(mlx.win, 6, 0, mouse_move, &mlx);
	mlx_loop_hook(mlx.mlx, key_hold_handler, &mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
	mlx_loop(mlx.mlx);
	return (0);
}
