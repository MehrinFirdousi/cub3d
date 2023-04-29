/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 20:22:27 by mfirdous          #+#    #+#             */
/*   Updated: 2023/04/29 18:41:20 by mfirdous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
# include <mlx.h>
# include <math.h>
# include <fcntl.h>

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define ESC 53
# define WHITE 16777215
# define GREEN 65280
# define GRAY 0X00808080
# define SPEED 5;

#  define W		13
#  define A		0
#  define S		1
#  define D		2

enum e_side
{
	E_NORTH,
	E_SOUTH,
	E_WEST,
	E_EAST
};

typedef struct s_player
{
	int		x;
	int		y;
	char	orientation;
}	t_player;

// typedef struct s_point
// {
// 	int		x;
// 	int		y;
// 	char	value;
// }	t_point;

typedef struct s_dda_dat
{
	int		dx;
	int		dy;
	int		dx_abs;
	int		dy_abs;
	int		steps;
	float	x_inc;
	float	y_inc;
}				t_dda_dat;

typedef struct s_map
{
	int		ceil_color;
	int		floor_color;
	char	*path_north;
	char	*path_south;
	char	*path_west ;
	char	*path_east ;
	char	**map;
	int		player_x;
	int		player_y;

	// t_list *map;
}	t_map;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_mlx
{
	void	*mlx;
	void	*win;
	t_img	*img;
	int		x_offset;
	int		y_offset;
}	t_mlx;


/* -------> Parse <-------- */
void	parsing(int argc, char **argv);
int		convert_texture(char *line, t_map *data, int flag);
t_map	*get_data(char *line);
int		cur_index(const char *str, char c);
int		valid_color(const char *str);
int	check_surface(const char *line);
void	put_error(const char *error);
void	get_colors(char *line, t_map *map);

int		key_click_handler(int keycode, t_mlx *m);
void	draw_blocks_2d(t_mlx *mlx);

#endif