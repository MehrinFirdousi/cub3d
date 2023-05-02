/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:25:33 by mfirdous          #+#    #+#             */
/*   Updated: 2023/05/02 16:57:33 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	deg_to_rad(double x)
{
	return (x * M_PI / 180.0);
}

void	mlx_set_up(t_mlx *mlx, t_img *img, t_player *pos, t_map *map)
{
	mlx->mlx = mlx_init();
	mlx->win = mlx_new_window(mlx->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3d");
	img->img = mlx_new_image(mlx->mlx, WIN_WIDTH, WIN_HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
								&img->line_length, &img->endian);
	pos->px = (pos->px * BLOCK_SIZE) + (BLOCK_SIZE / 2);
	pos->py = (pos->py * BLOCK_SIZE) + (BLOCK_SIZE / 2);
	pos->pa = deg_to_rad(270);
	pos->pdx = cos(pos->pa) * 5;
	pos->pdy = sin(pos->pa) * 5;
	mlx->img = img;
	mlx->pos = pos;
	mlx->map = map;
}

int	main(int argc, char **argv)
{
	t_mlx	mlx;
	t_img	img;
	t_player	pos;
	t_map	map;
	
	parsing(argc, argv, &map, &pos);
	print_map(&map, &pos);
	mlx_set_up(&mlx, &img, &pos, &map);
	// my_mlx_pixel_put(&img, 5, 5, 0x00FF0000); // 0,255,0,0
	draw_rays_2d(&mlx);
	draw_minimap(&mlx);
	
	mlx_key_hook(mlx.win, key_click_handler, &mlx);
	mlx_hook(mlx.win, 2, 1L << 0, key_hold_handler, &mlx);
	mlx_hook(mlx.win, 17, 0, exit_free, &mlx);
	
	mlx_put_image_to_window(mlx.mlx, mlx.win, img.img, 0, 0);
	mlx_loop(mlx.mlx);

	return (0);
}
