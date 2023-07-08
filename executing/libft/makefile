CC = cc
NAME = libft.a
CFLAGS = -Wall -Wextra -Werror
SRCS = 	ft_isdigit.c\
		ft_memmove.c\
		ft_strdup.c\
		ft_strncmp.c\
		ft_toupper.c\
		ft_isprint.c\
		ft_memset.c\
		ft_striteri.c\
		ft_atoi.c\
		ft_putchar_fd.c\
		ft_strjoin.c\
		ft_bzero.c\
		ft_itoa.c\
		ft_putendl_fd.c\
		ft_strlcat.c\
		ft_strnstr.c\
		ft_calloc.c\
		ft_putnbr_fd.c\
		ft_strlcpy.c\
		ft_strrchr.c\
		ft_isalnum.c\
		ft_memchr.c\
		ft_putstr_fd.c\
		ft_strtrim.c\
		ft_isalpha.c\
		ft_memcmp.c\
		ft_split.c\
		ft_strlen.c\
		ft_substr.c\
		ft_isascii.c\
		ft_memcpy.c\
		ft_strchr.c\
		ft_strmapi.c\
		ft_tolower.c\

BONUS = ft_lstnew.c\
		ft_lstadd_front.c\
		ft_lstsize.c\
		ft_lstlast.c\
		ft_lstadd_back.c\
		ft_lstdelone.c\
		ft_lstclear.c\
		ft_lstiter.c\
		ft_lstmap.c\

OBJDIR = objs

OBJCTS = $(addprefix $(OBJDIR)/, $(SRCS:.c=.o))
OBJCTSBONUS = $(addprefix $(OBJDIR)/, $(BONUS:.c=.o))

all: $(NAME)

bonus: $(OBJCTSBONUS) $(NAME)
	ar crs $(NAME) $(OBJCTS) $(OBJCTSBONUS)

$(OBJDIR):
	@mkdir -p $@


$(NAME): $(OBJDIR) $(OBJCTS) 
	ar crs $(NAME) $(OBJCTS)
$(OBJCTSBONUS): $(OBJDIR)/%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJCTS): $(OBJDIR)/%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: fclean clean all

re: fclean all
