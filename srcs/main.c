/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:25:33 by mfirdous          #+#    #+#             */
/*   Updated: 2023/05/11 19:53:17 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	deg_to_rad(double x)
{
	return (x * M_PI / 180.0);
}

void	print_colors(t_texture *texture)
{
	int	i;
	int	*colors;
	int	count;

	colors = (int *)texture->addr;
	i = -1;
	count = texture->width * texture->height;
	while (++i < count)
	{
		printf("%d - %d\n", i, colors[i]);
	}
}

void	get_textures_from_xpm(t_mlx *m)
{
	t_texture	*n;
	t_texture	*s;
	t_texture	*e;
	t_texture	*w;
	t_texture	*door_open;

	n = &m->map->n_texture;
	s = &m->map->s_texture;
	e = &m->map->e_texture;
	w = &m->map->w_texture;
	door_open = &m->map->c_door_texture;
	n->img = mlx_xpm_file_to_image(m->mlx, n->path, &n->width, &n->height);
	if (n->img)
		n->addr = mlx_get_data_addr(n->img, &n->bits_per_pixel, &n->line_length,
				&n->endian);
	s->img = mlx_xpm_file_to_image(m->mlx, s->path, &s->width, &s->height);
	if (s->img)
		s->addr = mlx_get_data_addr(s->img, &s->bits_per_pixel, &s->line_length,
				&s->endian);
	e->img = mlx_xpm_file_to_image(m->mlx, e->path, &e->width, &e->height);
	if (e->img)
		e->addr = mlx_get_data_addr(e->img, &e->bits_per_pixel, &e->line_length,
				&e->endian);
	w->img = mlx_xpm_file_to_image(m->mlx, w->path, &w->width, &w->height);
	if (w->img)
		w->addr = mlx_get_data_addr(w->img, &w->bits_per_pixel, &w->line_length,
				&w->endian);
	door_open->img = mlx_xpm_file_to_image(m->mlx, door_open->path, &door_open->width, &door_open->height);
	if (door_open->img)
		door_open->addr = mlx_get_data_addr(door_open->img, &door_open->bits_per_pixel, &door_open->line_length,
				&door_open->endian);
}

void	get_torch_sprite(t_mlx *m)
{
	t_texture	*t;
	int			i;

	t = &m->map->torch[0];
	i = -1;
	while (++i < FRAME_TOTAL)
		t[i].img = mlx_xpm_file_to_image(m->mlx, t[i].path, &t[i].width, &t[i].height);
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
	m->map->torch_frame = 0;
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
	print_map(&map, &p);
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
