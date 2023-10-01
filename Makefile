CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I includes 
RM			= rm -rf
MKDIR		= mkdir -p
USERS		= $(USER)

OS              =       $(shell uname -s)
ifeq ($(OS),Linux)
	LINK 		= -lreadline
else
	COMP        = -L/goinfre/$(USERS)/.brew/opt/readline/lib
	LINK 		= -I/goinfre/$(USERS)/.brew/opt/readline/include
endif

SRCS = 	main.c\
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
		libft/ft_atoi.c \
        libft/ft_bzero.c \
        libft/ft_calloc.c \
        libft/ft_isalnum.c \
        libft/ft_contains.c \
        libft/ft_isalpha.c \
        libft/ft_isascii.c \
        libft/ft_isdigit.c \
        libft/ft_isprint.c \
        libft/ft_itoa.c \
        libft/ft_memchr.c \
        libft/ft_memcmp.c \
        libft/ft_memcpy.c \
        libft/ft_memmove.c \
        libft/ft_memset.c \
        libft/ft_putchar_fd.c \
        libft/ft_putendl_fd.c \
        libft/ft_putnbr_fd.c \
        libft/ft_putstr_fd.c \
        libft/ft_split.c \
        libft/ft_strchr.c \
        libft/ft_strdup.c \
        libft/ft_striteri.c \
        libft/ft_strjoin.c \
        libft/ft_strjoin_sep.c \
        libft/ft_strlcat.c \
        libft/ft_strlcpy.c \
        libft/ft_strlen.c \
        libft/ft_strmapi.c \
        libft/ft_strncmp.c \
        libft/ft_strcmp.c \
        libft/ft_strnstr.c \
        libft/ft_strrchr.c \
        libft/ft_strtrim.c \
        libft/ft_substr.c \
        libft/ft_tolower.c \
        libft/ft_toupper.c \
        libft/ft_lstadd_back.c \
        libft/ft_lstnew.c \
        libft/ft_lstsize.c \
        libft/ft_lstlast.c \
        libft/ft_lstadd_front.c \

BIN_DIR		= bin/

OBJS		= $(SRCS:%.c=$(BIN_DIR)%.o)
OBJS_DIRS	= $(dir $(OBJS))

INCLUDES	= includes/exec.h includes/lexer.h 

NAME		= minishell


all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) $(LINK)

$(BIN_DIR)%.o: %.c $(INCLUDES)
	@$(MKDIR) $(OBJS_DIRS)
	$(CC) $(COMP) $(CFLAGS)  -c $< -o $@ 

clean:
	@$(RM) $(BIN_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all
