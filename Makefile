# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carys <carys@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/30 10:42:54 by carys             #+#    #+#              #
#    Updated: 2022/10/04 20:24:48 by carys            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3d

HEADER	=	cub3d.h

SRCS	=	main.c move.c minimap.c hook.c check_map.c free.c rotation.c ray_cast.c draw.c\
			parsing.c parsing_utils.c make utils_one.c utils_two.c
			
OBJS	=	${SRCS:%.c=%.o}

CC		=	gcc

RM		=	rm -f

BGN		=	START
END		=	FINISH
CLR		=	\001\033[1;92m\002
RST		=	\001\033[0m\002

CFLAGS	=	-Wall -Wextra -Werror -I${HEADER}

MLX_FLAGS =	-lmlx -framework OpenGL -framework AppKit

.PHONY:		all clean fclean re

all:		${NAME}

%.o: 		%.c ${HEADER}
			${CC} ${CFLAGS} -c $< -o $@

${NAME}:	${OBJS} ${HEADER}
			${CC} ${CFLAGS} ${MLX_FLAGS} -o ${NAME} ${OBJS}
			@printf "${CLR}${BGN}${RST}\n"

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}
			@printf "${CLR}${END}${RST}\n"

re:			fclean all

norm:
			@norminette ${SRCS} ${HEADER}
