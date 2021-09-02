# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: al-humea <al-humea@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/27 19:23:51 by al-humea          #+#    #+#              #
#    Updated: 2021/09/02 15:06:38 by al-humea         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=		gcc

INCLUDES=		./includes/minitalk.h

SRV_SRC=		server.c

CLT_SRC=		client.c

UTILS=		utils/ft_putstr_fd.c\
			utils/ft_strdup.c\
			utils/ft_strlen.c\
			utils/ft_putchar_fd.c\
			utils/ft_itoa.c\
			utils/display_pid.c\
			utils/chrjoin.c\

SERVER=		server

CLIENT=		client

CFLAGS=		-Wall -Wextra -Werror -g -pg

MV=			mv

RM=			rm -f

SRV_OBJ=	$(SRV_SRC:.c=.o)

CLT_OBJ=	$(CLT_SRC:.c=.o)

UTL_OBJ=	$(UTILS:.c=.o)

$(SERVER):	$(SRV_OBJ) $(UTL_OBJ) $(CLIENT)
	$(CC) $(CFLAGS) -I$(INCLUDES) $(SRV_OBJ) $(UTL_OBJ) -o $(SERVER)

$(CLIENT):	$(CLT_OBJ)
	$(CC) $(CFLAGS) -I$(INCLUDES) $(CLT_OBJ) $(UTL_OBJ) -o $(CLIENT)


all:	$(SERVER) $(CLIENT)

clean:
	$(RM) $(SRV_OBJ)
	$(RM) $(CLT_OBJ)
	$(RM) $(UTL_OBJ)

fclean:	clean
	$(RM) $(SERVER)
	$(RM) $(CLIENT)

re:	fclean all

.PHONY:	all clean fclean re