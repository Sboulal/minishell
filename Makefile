# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 17:27:32 by saboulal          #+#    #+#              #
#    Updated: 2023/09/13 16:21:42 by saboulal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
CC = cc
libft = libft/libft.a
CFLAGS = -Wall -Wextra -Werror 
#L = -L/Users/saboulal/.brew/opt/readline/lib
#I = -I/Users/saboulal/.brew/opt/readline/include
SRC = 	main.c\
		lexer/lexer_util.c\
		lexer/lexer.c\
		lexer/checks.c\
		lexer/linked_list.c\
		lexer/linked_list2.c\
		lexer/lexer_utils2.c\
		expansion/expand.c\
		expansion/expand_utils.c\
		parser/parsing.c\
		parser/chekcs_words.c\
		parser/enviroment.c\
		parser/fill_cmd_to_execute.c\
		parser/herdoc.c\
		parser/handle_all.c\
		parser/need_this_func.c\
		
OBJCTS = $(SRC:.c=.o)
all : $(NAME)
$(NAME) : $(OBJCTS) $(libft)
		$(CC) $(CFLAGS) $^ -o $@  -lreadline 

%.o: %.c lexer.h
	$(CC) $(CFLAGS) -c $< -o $@

$(libft) :
	make -C libft
	
clean:
	rm -f $(OBJCTS)
	make -C libft clean 

fclean: clean
	 rm -f $(NAME) $(libft)

re: fclean all

.PHONY: fclean clean all re