/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saboulal  <saboulal@student.1337.ma>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 16:25:08 by saboulal          #+#    #+#             */
/*   Updated: 2023/07/12 14:08:01 by saboulal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <stdlib.h>
typedef enum e_token
{
	WORD = -1,
	WHITE_SPACE = ' ',
	NEW_LINE = '\n',
	QOUTE = '\'',
	DOUBLE_QOUTE = '\"',
	ESCAPE = '\\',
	ENV = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
	AND = '&',
	HERE_DOC,
	DREDIR_OUT,
}t_token;

enum e_state
{
   IN_DQUOTE,
   IN_QUOTE,
   GENERAL,
};

// for lexer 
typedef struct s_lexer
{
   char *str;
   int lenght;
   enum e_token type;
   enum	e_state state;
   struct s_lexer *next ;
   struct s_lexer *prev;
}t_lexer;

typedef struct s_list
{
   
 int		how;
 t_lexer  *head;
 t_lexer  *last;
}t_list;




char	**ft_split(char const *s, char c);
char	*ft_strdup(const char	*str);
int	ft_strlen(const char *str);
void	*ft_calloc(size_t em, size_t emz);
void	ft_bzero(void *s, size_t n);
void	*ft_memset(void *p, int c, size_t len);


#endif