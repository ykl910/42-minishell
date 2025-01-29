# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kyang <kyang@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/29 15:15:05 by kyang             #+#    #+#              #
#    Updated: 2025/01/29 16:14:34 by kyang            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc

SRC_PATH = src/
SRC 	= main.c

SRCS	= $(addprefix $(SRC_PATH), $(SRC))

LIBFT = ./libft

CFLAGS = -Wall -Wextra -Werror 

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	make all bonus -C libft
	$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a -o $(NAME) -lreadline
	
%.o: %.c
	$(CC) $(CFLAGS) -Iinclude -I $(LIBFT) -O3 -c $< -o $@ 

clean:
	rm -f $(OBJS)
	make -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT) fclean
	
re: fclean all

.PHONY: all clean fclean re bonus