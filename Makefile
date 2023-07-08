CC = cc
LIBFT = libft/libft.a
CFLAGS = -Wall -Wextra -Werror 
NAME = minishell
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
$(NAME) : $(OBJCTS) $(LIBFT)
		$(CC) $(CFLAGS) $(LIBFT) -lreadline $^ -o $@ 

%.o: %.c minishell.h
	$(CC) $(CFLAGS) -c $< -o $@ 
	
$(LIBFT):
	make -C libft

clean:
	rm -f $(OBJCTS)
	make -C libft clean

fclean: clean
	rm -f $(NAME) $(LIBFT)

re: fclean all

.PHONY: fclean clean all re 