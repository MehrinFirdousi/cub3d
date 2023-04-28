# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/26 20:19:54 by mfirdous          #+#    #+#              #
#    Updated: 2023/04/28 10:38:57 by ahassan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

SRCS	=	srcs/main.c \
			srcs/get_data.c \
			srcs/parse.c \
			srcs/textures_data.c \
			srcs/colors_data.c \
			srcs/parse_utils.c \
			srcs/key_handler.c

OBJS	=	${SRCS:.c=.o}

HEADER	=	include

LIBFT	=	libft/libft.a

MLX		=	libmlx.dylib

CC		=	gcc

MLX_DIR		=	mlx

CFLAGS	=	 -Wall -Wextra -Werror -I ${HEADER} -I ${MLX_DIR} -Ofast

MLX_FLAGS	= -L. -lmlx -framework OpenGL -framework AppKit

#.c.o:
#			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

${NAME}:	${LIBFT} ${MLX} ${OBJS}
			${CC} ${CFLAGS} ${MLX_FLAGS} ${OBJS} ${LIBFT} -o ${NAME}

${LIBFT}:
			${MAKE} -C libft

${MLX}:
			${MAKE} -C mlx
			mv mlx/libmlx.dylib .

all:		${NAME}

clean:
			rm -f ${OBJS}
			rm -f ${MLX}
			${MAKE} -C libft clean
			${MAKE} -C mlx clean

fclean:		clean
			rm -f ${NAME}
			${MAKE} -C libft fclean

re:			fclean all

.PHONY:		all clean fclean re