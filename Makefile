# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfirdous <mfirdous@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/26 20:19:54 by mfirdous          #+#    #+#              #
#    Updated: 2023/05/12 16:01:06 by mfirdous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

SRCS	=	srcs/main.c \
			srcs/get_data.c \
			srcs/parse.c \
			srcs/get_upper_map.c \
			srcs/get_textures.c \
			srcs/get_colors.c \
			srcs/get_map.c \
			srcs/check_valid_map.c \
			srcs/parse_utils.c \
			srcs/extra_parse_utils.c \
			srcs/bonus_parse.c \
			srcs/key_handler.c \
			srcs/key_handler_utils.c \
			srcs/mouse_handler.c \
			srcs/draw_minimap.c \
			srcs/draw_scene.c \
			srcs/draw_texture.c \
			srcs/draw_utils.c \
			srcs/redraw_image.c \
			srcs/exit_free.c
			

OBJS	=	${SRCS:.c=.o}

HEADER	=	include

LIBFT	=	libft/libft.a

# CC		=	gcc -fsanitize=address,undefined,float-divide-by-zero -g3
CC		=	gcc -g3

OS		:=	$(shell uname)

ifeq ($(OS),Linux)
	MLX			=	libmlx.a
	MLX_DIR		=	mlx_linux
	CFLAGS		=	-Wall -Wextra -I${HEADER} -I/usr/include -I ${MLX_DIR} -O3 -Ofast
	MLX_FLAGS	=	-Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lm -lXext -lX11 -lz
else
	MLX			=	libmlx.dylib
	MLX_DIR		=	mlx
	CFLAGS		=	-Wall -Werror -Wextra -I ${HEADER} -I ${MLX_DIR} -Ofast
	MLX_FLAGS	=	-L. -lmlx -framework OpenGL -framework AppKit
endif

${NAME}:	${LIBFT} ${MLX} ${OBJS}
			${CC} ${CFLAGS} ${OBJS} ${LIBFT} ${MLX_FLAGS} -o ${NAME} 

${LIBFT}:
			${MAKE} -C libft

${MLX}:
			${MAKE} -C ${MLX_DIR}
			mv ${MLX_DIR}/${MLX} .

all:		${NAME}

clean:
			rm -f ${OBJS}
			rm -f ${MLX}
			${MAKE} -C libft clean
			${MAKE} -C ${MLX_DIR} clean

fclean:		clean
			rm -f ${NAME}
			${MAKE} -C libft fclean

bonus:		all

re:			fclean all

.PHONY:		all clean fclean rea
