# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/31 16:07:55 by ededemog          #+#    #+#              #
#    Updated: 2025/01/31 18:04:03 by ededemog         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CFLAGS = -Wall -Wextra -Werror -pthread -g
RM = rm -rf
SRCS = 	srcs/main.c\
		srcs/init.c\
		srcs/utils.c\
		srcs/philo.c\
		srcs/clean.c\
		srcs/philo2.c\
		srcs/simu.c\
		srcs/parser.c\

.PHONY: all clean fclean re

$(NAME):
	gcc $(CFLAGS) $(SRCS) -o $(NAME)

all: $(NAME)

fclean: clean
	$(RM) $(NAME)

clean:
	$(RM) *.o $(NAME)

re: fclean all