/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:59:19 by mfirdous          #+#    #+#             */
/*   Updated: 2023/05/12 15:59:53 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_texture(t_mlx *m, t_texture *t)
{
	if (t->path)
		free(t->path);
	if (t->img)
		mlx_destroy_image(m->mlx, t->img);
}

int	exit_free(t_mlx *m)
{
	int	i;

	i = -1;
	while (++i < FRAME_TOTAL)
		free_texture(m, &m->map->torch[i]);
	mlx_destroy_image(m->mlx, m->img->img);
	free_texture(m, &m->map->n_texture);
	free_texture(m, &m->map->s_texture);
	free_texture(m, &m->map->w_texture);
	free_texture(m, &m->map->e_texture);
	free_texture(m, &m->map->c_door_texture);
	free(m->map->file);
	free(m->rays);
	ft_split_destroy(m->map->map);
	exit(0);
}
