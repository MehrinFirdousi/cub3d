/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:22:27 by mfirdous          #+#    #+#             */
/*   Updated: 2023/04/27 16:48:10 by ahassan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <mlx.h>
# include <math.h>

enum e_side
{
	E_NORTH,
	E_SOUTH,
	E_WEST,
	E_EAST
};


typedef struct s_data 
{
	char *path_north;
	char *path_south;
	char *path_west ;
	char *path_east ;
} t_data;

void	parsing(int argc, char **argv);
t_data	*get_data(char *line);
void	put_error(const char *error);

#endif