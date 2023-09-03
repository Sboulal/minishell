# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 17:27:32 by saboulal          #+#    #+#              #
#    Updated: 2023/07/12 19:32:12 by saboulal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror 
L = -L/Users/saboulal/.brew/opt/readline/lib
I = -I/Users/saboulal/.brew/opt/readline/include
SRC = 	main.c\
		libft/ft_strlen.c\
		

OBJCTS = $(SRC:.c=.o)
all : $(NAME)
$(NAME) : $(OBJCTS) 
		$(CC) $(CFLAGS) $^ -o $@  -lreadline $(L)
%.o: %.c lexer.h
	$(CC) $(CFLAGS) -c $< -o $@ $(I)
	
clean:
	rm -f $(OBJCTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: fclean clean all re bonus