CC = cc
LIBFT = libft/libft.a
CFLAGS = -Wall -Wextra -Werror 
NAME = exec
SRC = \
		builtins/main.c\
		builtins/cd.c\
		builtins/echo.c\
		builtins/env.c\
		builtins/exit.c\
		builtins/export.c\
		builtins/pwd.c\
		builtins/unset.c\

OBJCTS = $(SRC:.c=.o)
all : $(NAME)
$(NAME) : $(OBJCTS) $(LIBFT)
		$(CC) $(CFLAGS) $(LIBFT) -lreadline $^ -o $@ 

%.o: %.c exic.h
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