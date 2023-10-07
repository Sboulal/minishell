NAME = minishell
CC = cc
libft = libft/libft.a
# USER = $(shell whoami)
CFLAGS = -Wall -Wextra -Werror -I/Users/$(USER)/.brew/opt/readline/include #-g  -fsanitize=address 
RLFLAGES = -lreadline -lhistory -L/Users/$(USER)/.brew/opt/readline/lib
#L = -L/Users/saboulal/.brew/opt/readline/lib
#I = -I/Users/saboulal/.brew/opt/readline/include
SRC = 	main.c\
		lexer/lexer_util.c\
		lexer/lexer.c\
		lexer/checks.c\
		lexer/checks_utils2.c\
		lexer/checks_utils.c\
		lexer/linked_list.c\
		lexer/linked_list2.c\
		lexer/lexer_utils2.c\
		expansion/expand.c\
		expansion/expand_util_2.c\
		expansion/expand_utils.c\
		expansion/expand_norm.c\
		expansion/expand_norm_2.c\
		parser/parsing.c\
		parser/chekcs_words.c\
		parser/enviroment.c\
		parser/fill_cmd_to_execute.c\
		parser/herdoc.c\
		parser/handle_all.c\
		parser/need_this_func.c\
		executing/builtins/cd.c\
		executing/builtins/cd_util.c\
		executing/builtins/builtin.c\
		executing/builtins/builtin_utils.c\
		executing/builtins/echo.c\
		executing/builtins/env.c\
		executing/builtins/exit.c\
		executing/builtins/export.c\
		executing/builtins/export_utile.c\
		executing/builtins/export_utils_2.c\
		executing/builtins/export_util_3.c\
		executing/builtins/pwd.c\
		executing/builtins/unset.c\
		executing/builtins/unset_util.c\
		executing/builtins/creat_env_struct.c\
		executing/builtins/export_utile.c\
		executing/builtins/creat_export.c\
		executing/builtins/export_norm.c\
		executing/exec/exec.c\
		executing/exec/pipe.c\
		executing/exec/pipe_utils.c\
		executing/signal.c\
	
OBJCTS = $(SRC:.c=.o)
all : $(NAME)
$(NAME) : $(OBJCTS) $(libft) 
		$(CC) $(CFLAGS) $(RLFLAGES) $^ -o $@  -lreadline 

%.o: %.c includes/lexer.h includes/exec.h libft/libft.h
	$(CC) $(CFLAGS) -c $< -o $@

$(libft) : libft/libft.h
	make -C libft
	
clean:
	rm -f $(OBJCTS)
	make -C libft clean 

fclean: clean
	 rm -f $(NAME) $(libft)

re: fclean all

.PHONY: fclean clean all re
