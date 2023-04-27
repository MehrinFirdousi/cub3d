# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahassan <ahassan@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/26 20:19:54 by mfirdous          #+#    #+#              #
#    Updated: 2023/04/27 16:53:29 by ahassan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

SRCS	=	srcs/main.c srcs/get_data.c srcs/parse.c\

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