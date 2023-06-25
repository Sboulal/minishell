# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 17:27:32 by saboulal          #+#    #+#              #
#    Updated: 2023/06/25 20:57:11 by nkhoudro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror 
SRC = \
		main.c\
		mini_tool/ft_split.c\
		mini_tool/ft_strdup.c\
		mini_tool/ft_strlen.c\
		mini_tool/ft_substr.c\
		mini_tool/ft_strlcpy.c\
		mini_tool/ft_isalpha.c\
		mini_tool/ft_strchr.c\

OBJCTS = $(SRC:.c=.o)
all : $(NAME)
$(NAME) : $(OBJCTS) 
		$(CC) $(CFLAGS) -lreadline $^ -o $@
%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@ 
	
clean:
	rm -f $(OBJCTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: fclean clean all re bonus