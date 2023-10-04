# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/10 17:01:31 by saboulal          #+#    #+#              #
#    Updated: 2023/09/19 21:22:14 by nkhoudro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = libft.a

SRCS = ft_atoi.c \
    ft_bzero.c \
    ft_calloc.c \
    ft_isalnum.c \
    ft_contains.c \
    ft_isalpha.c \
    ft_isascii.c \
    ft_isdigit.c \
    ft_isprint.c \
    ft_itoa.c \
    ft_memchr.c \
    ft_memcmp.c \
    ft_memcpy.c \
    ft_memmove.c \
    ft_memset.c \
    ft_putchar_fd.c \
    ft_putendl_fd.c \
    ft_putnbr_fd.c \
    ft_putstr_fd.c \
    ft_split.c \
    ft_strchr.c \
    ft_strdup.c \
    ft_striteri.c \
    ft_strjoin.c \
    ft_strjoin_sep.c \
    ft_strlcat.c \
    ft_strlcpy.c \
    ft_strlen.c \
    ft_strmapi.c \
    ft_strncmp.c \
    ft_strcmp.c \
    ft_strnstr.c \
    ft_strrchr.c \
    ft_strtrim.c \
    ft_substr.c \
    ft_tolower.c \
    ft_toupper.c \
    ft_lstadd_back.c \
    ft_lstnew.c \
    ft_lstsize.c \
    ft_lstlast.c \
    ft_lstadd_front.c  \
       
        
OBJS = ${SRCS:.c=.o}
OBJSBONUS = ${Bonus:.c=.o}

CC = cc

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

all: ${NAME}

$(NAME): $(OBJS)
	ar -rc $(NAME) $(OBJS)

%.o: %.c libft.h 
	$(CC) $(CFLAGS) -c $<

bonus: $(OBJS) $(OBJSBONUS)
	ar -rc $(NAME) $(OBJS) $(OBJSBONUS)

clean:
	$(RM) $(OBJS) $(OBJSBONUS)

fclean: clean
	$(RM) $(NAME)

re: fclean all 
