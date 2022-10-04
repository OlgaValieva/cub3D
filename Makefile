# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carys <carys@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/30 10:42:54 by carys             #+#    #+#              #
#    Updated: 2022/10/04 15:27:10 by carys            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3d

HEADER	=	cub3d.h

SRCS	=	src/main.c src/move.c src/minimap.c\				
			src/hook.c src/check_map.c src/free.c\		
			src/rotation.c src/ray_cast.c src/draw.c\			
			src/paint.c src/parsing.c src/parsing_utils.c\				
			src/utils_one.c src/utils_two.c

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
			@echo "---Compiled "$<" success!---"

${NAME}:	${OBJS_A} ${HEADER}
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