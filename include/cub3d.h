/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:22:27 by mfirdous          #+#    #+#             */
/*   Updated: 2023/04/27 19:57:09 by mfirdous         ###   ########.fr       */
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
	char	*path_north;
	char	*path_south;
	char	*path_west ;
	char	*path_east ;
}	t_data;

typedef struct s_player
{
	int		x;
	int		y;
	char	orientation;
}	t_player;

typedef struct s_map
{
	int		ceil_color;
	int		floor_color;
	// texture paths - 4
	char	**map;
}	t_map;

void	parsing(int argc, char **argv);
t_data	*get_data(char *line);
void	put_error(const char *error);

#endif