# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/10 17:27:32 by saboulal          #+#    #+#              #
#    Updated: 2023/09/20 15:11:12 by saboulal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = minishell
CC = cc
libft = libft/libft.a
USER = $(shell whoami)
CFLAGS = -Wall -Wextra -Werror -I/Users/$(USER)/.brew/opt/readline/include #-g -fsanitize=address
RLFLAGES = -lreadline -lhistory -L/Users/$(USER)/.brew/opt/readline/lib
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
		executing/builtins/cd.c\
		executing/builtins/builtin.c\
		executing/builtins/echo.c\
		executing/builtins/env.c\
		executing/builtins/exit.c\
		executing/builtins/export.c\
		executing/builtins/pwd.c\
		executing/builtins/unset.c\
		executing/builtins/creat_env_struct.c\
		executing/builtins/export_utile.c\
		executing/builtins/creat_export.c\
		executing/exec/exec.c\
		executing/exec/pipe.c\
		executing/exec/pipe_utils.c\
		executing/signal.c\
		
OBJCTS = $(SRC:.c=.o)
all : $(NAME)
$(NAME) : $(OBJCTS) $(libft)
		$(CC) $(CFLAGS) $(RLFLAGES) $^ -o $@  -lreadline 

%.o: %.c headers/lexer.h headers/exec.h
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