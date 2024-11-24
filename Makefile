# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ededemog <ededemog@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/29 16:12:40 by ededemog          #+#    #+#              #
#    Updated: 2024/11/08 00:23:14 by ededemog         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CFLAGS = -Wall -Wextra -Werror -pthread
RM = rm -rf
SRCS = 	src/main.c\
		src/init.c\
		src/utils.c\
		src/philo.c\
		src/clean.c

.PHONY: all clean fclean re

$(NAME):
	gcc $(CFLAGS) $(SRCS) -o $(NAME)

all: $(NAME)

fclean: clean
	$(RM) $(NAME)

clean:
	$(RM) *.o $(NAME)

re: fclean all