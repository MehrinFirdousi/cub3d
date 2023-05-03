/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:25:33 by mfirdous          #+#    #+#             */
/*   Updated: 2023/05/03 23:47:33 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	deg_to_rad(double x)
{
	return (x * M_PI / 180.0);
}

void	mlx_set_up(t_mlx *m)
{
	m->mlx = mlx_init();
	m->win = mlx_new_window(m->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	m->img->img = mlx_new_image(m->mlx, WIN_WIDTH, WIN_HEIGHT);
	m->img->addr = mlx_get_data_addr(m->img->img, &m->img->bits_per_pixel, \
								&m->img->line_length, &m->img->endian);
	m->p->px = (m->p->px * MM_SIZE) + (MM_SIZE / 2);
	m->p->py = (m->p->py * MM_SIZE) + (MM_SIZE / 2);
	m->p->pdx = cos(m->p->pa) * 5;
	m->p->pdy = sin(m->p->pa) * 5;
	m->rays = ft_malloc(WIN_WIDTH * sizeof(t_point));
	ft_bzero(m->keys, sizeof(t_keys));
}

int	main(int argc, char **argv)
{
	t_mlx		mlx;
	t_img		img;
	t_player	p;
	t_map		map;
	t_keys		keys;

	parsing(argc, argv, &map, &p);
	print_map(&map, &p);
	
	mlx.img = &img;
	mlx.p = &p;
	mlx.map = &map;
	mlx.keys = &keys;
	
	mlx_set_up(&mlx);
	// my_mlx_pixel_put(&img, 5, 5, 0x00FF0000); // 0,255,0,0
	draw_scene(&mlx);
	draw_minimap(&mlx);
	
	mlx_key_hook(mlx.win, key_up_handler, &mlx);
	mlx_hook(mlx.win, 2, 1L << 0, key_down_handler, &mlx);
	mlx_hook(mlx.win, 17, 0, exit_free, &mlx);
	mlx_loop_hook(mlx.mlx, key_hold_handler, &mlx);
	
	mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
	mlx_loop(mlx.mlx);

	return (0);
}
