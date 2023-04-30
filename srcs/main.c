/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:25:33 by mfirdous          #+#    #+#             */
/*   Updated: 2023/04/30 15:21:03 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	exit_free(t_mlx *m)
{
	mlx_destroy_image(m->mlx, m->img->img);
	// free any alloced mem here
	exit(0);
}

double	deg_to_rad(double x)
{
	return (x * (M_PI / 180.0));
}

void	mlx_set_up(t_mlx *mlx, t_img *img, t_pos *pos)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	img->img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
								&img->line_length, &img->endian);
	pos->px = 0;
	pos->py = 0;
	pos->pa = deg_to_rad(270);
	pos->pdx = cos(pos->pa) * 5;
	pos->pdy = sin(pos->pa) * 5;
	mlx->img = img;
	mlx->pos = pos;
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_img	img;
	t_pos	pos;

	parsing(argc, argv);
	mlx_set_up(&mlx, &img, &pos);
	// my_mlx_pixel_put(&img, 5, 5, 0x00FF0000); // 0,255,0,0
	draw_blocks_2d(&mlx);
	draw_rays_2d(&mlx);
	mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);

	mlx_key_hook(mlx.win, key_click_handler, &mlx);
	mlx_hook(mlx.win, 2, 0, key_hold_handler, &mlx);
	mlx_hook(mlx.win, 17, 0, exit_free, &mlx);
	mlx_loop(mlx.mlx);

	return (0);
}
