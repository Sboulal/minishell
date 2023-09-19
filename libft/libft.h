/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkhoudro <nkhoudro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 21:31:05 by saboulal          #+#    #+#             */
/*   Updated: 2023/09/19 21:23:01 by nkhoudro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include<unistd.h>
# include<stddef.h>
# include<stdio.h>
# include<stdlib.h>

size_t	ft_strlen(const char *str);
int		ft_toupper(int a);
int		ft_tolower(int a);
int		ft_isalnum(int a);
int		ft_isalpha(int a);
int		ft_isascii(int a);
int		ft_isdigit(int a);
int		ft_isprint(int a);
int		contains(char *s, char c);
void	*ft_memchr(const void *mb, int sc, size_t len);
int		ft_memcmp(const void *p, const void *p2, size_t l);
void	*ft_memcpy( void *dst, void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t len);
void	*ft_memset(void *p, int c, size_t len);
char	**ft_split(char const *s, char c);
char	*ft_strchr(const char *str, int search);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlcat(char *dest, const char *src, size_t len);
int		ft_strncmp(const char *f, const char *s, size_t len);
int	ft_strcmp(const char *s1, const char *s2);
char	*ft_strnstr(const char *str, const char *to_find, size_t n);
char	*ft_strrchr(const char *str, int c);
char	*ft_strdup(const char *str);
void	*ft_calloc(size_t nm);
char	*ft_itoa(int nb);
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int nb, int fd);
void	ft_putstr_fd(char *s, int fd);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strmapi(char const *s, char (*f) (unsigned int, char));
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strjoin_sep(char *s1, char *s2, char sep);
char	*ft_strtrim(char const *s1, char const *set);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_atoi(const char *str);
void	ft_bzero( void *s, size_t n);

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
void	ft_lstadd_front(t_list **lst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
int		ft_lstsize(t_list *lst);

#endif
