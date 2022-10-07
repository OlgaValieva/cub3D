# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: carys <carys@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/30 10:42:54 by carys             #+#    #+#              #
#    Updated: 2022/10/07 14:50:31 by carys            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3d

HEADER	=	cub3d.h

SRCS	=	check_map.c draw.c free.c hook.c main.c minimap.c move.c\
			ray_cast.c rotation.c parsing.c parsing_utils.c utils_one.c utils_two.c
			
OBJS	=	${SRCS:%.c=%.o}

CC		=	cc

RM		=	rm -f

CLR		=	\001\033[1;92m\002
RST		=	\001\033[0m\002

CFLAGS	=	-Wall -Wextra -Werror -I${HEADER}

MLX_FLAGS =	-Lmlx -lmlx -framework OpenGL -framework AppKit

.PHONY:		all clean fclean re

all:		${NAME}

%.o: 		%.c ${HEADER}
			${CC} ${CFLAGS} -Imlx -c $< -o $@

${NAME}:	${OBJS} ${HEADER}
			${CC} ${CFLAGS} ${MLX_FLAGS} -o ${NAME} ${OBJS}
			@printf "${CLR}"START" $(NAME)""${RST}\n"

clean:
			${RM} ${OBJS}

fclean:		clean
			${RM} ${NAME}
			@printf "${CLR}"FINISH" $(NAME)""${RST}\n"

re:			fclean all
			@printf "${CLR}"REBOOT" $(NAME)""${RST}\n"

norm:
			@printf "${CLR}"NORMINETTE" $(NAME)""${RST}\n"
			@norminette ${SRCS} ${HEADER}
