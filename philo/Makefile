# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: shassoun <shassoun@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/20 17:15:43 by shassoun          #+#    #+#              #
#    Updated: 2024/11/25 00:25:23 by shassoun         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = main.c current_time.c routines.c ft_atoi.c actions.c 

OBJS = $(SRC:.c=.o)

all:$(NAME)
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean :
	rm -f $(OBJS)

fclean: clean 
	rm -f $(NAME)

re: fclean all 

.PHONY: clean

.SECONDARY: