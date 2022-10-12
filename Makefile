# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cyetta <cyetta@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/30 10:42:54 by carys             #+#    #+#              #
#    Updated: 2022/10/11 17:22:37 by cyetta           ###   ########.fr        #
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

.PHONY:		all clean fclean re debug mlx

DPDS	= ${SRCS:.c=.d}

all:		${NAME}

%.o: %.c
			${CC} ${CFLAGS} ${DFLAG} -MMD -c $< -o $@  -Imlx

mlx:
		${MAKE} -C mlx 

include ${wildcard ${DPDS}}

${NAME}:	mlx ${OBJS}
			${CC} ${CFLAGS} ${DFLAG} ${MLX_FLAGS} -o ${NAME} ${OBJS}
			@printf "${CLR}"START" $(NAME)""${RST}\n"

debug:
			${MAKE} DFLAG="-g3" ${NAME}
clean:
			${RM} ${OBJS} ${DPDS}

fclean:		clean
			${MAKE} -C mlx clean
			${RM} ${NAME}
			@printf "${CLR}"'Full cleanup '"$(NAME)""${RST}\n"

re:			fclean all
			@printf "${CLR}"REBOOT" $(NAME)""${RST}\n"

norm:
			@printf "${CLR}"NORMINETTE" $(NAME)""${RST}\n"
			@norminette ${SRCS} ${HEADER}
